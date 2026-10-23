/**
 * DT053 - MINIMUM PATH SUM VISUALIZER
 * Sinh viên: Ngô Lê Tấn Nhân - MSSV: N24DCDT059
 */

// Presets data
const PRESETS = {
    vd1: [
        [1, 3, 1],
        [1, 5, 1],
        [4, 2, 1]
    ],
    vd2: [
        [2, 4, 1]
    ],
    hinh44: [
        [1, 3, 1, 2],
        [1, 5, 1, 3],
        [4, 2, 1, 1],
        [2, 1, 4, 1]
    ],
    cot1: [
        [2],
        [4],
        [1]
    ],
    hoa: [
        [1, 1],
        [1, 1]
    ],
    zigzag: [
        [1, 9, 9, 9],
        [1, 1, 9, 9],
        [9, 1, 1, 9],
        [9, 9, 1, 1]
    ]
};

// Application State
let state = {
    m: 3,
    n: 3,
    C: [
        [1, 3, 1],
        [1, 5, 1],
        [4, 2, 1]
    ],
    f: [],
    path: [],
    fromDir: [], // 'left', 'top', or 'start'
    animationRunning: false,
    timerId: null,
    stepSpeed: 300
};

// DOM Elements
const inputRows = document.getElementById('inputRows');
const inputCols = document.getElementById('inputCols');
const btnApplySize = document.getElementById('btnApplySize');
const selectPattern = document.getElementById('selectPattern');
const gridSizeControls = document.getElementById('gridSizeControls');
const presetNotice = document.getElementById('presetNotice');
const btnSolve = document.getElementById('btnSolve');
const btnStepByStep = document.getElementById('btnStepByStep');
const btnReset = document.getElementById('btnReset');
const rangeSpeed = document.getElementById('rangeSpeed');
const speedDisplay = document.getElementById('speedDisplay');
const gridC = document.getElementById('gridC');
const gridF = document.getElementById('gridF');
const stepStatusIndicator = document.getElementById('stepStatusIndicator');
const explanationText = document.getElementById('explanationText');
const resultTotalSum = document.getElementById('resultTotalSum');
const resultStepCount = document.getElementById('resultStepCount');
const resultOptSpace = document.getElementById('resultOptSpace');
const resultPathDisplay = document.getElementById('resultPathDisplay');
const btnCopyPath = document.getElementById('btnCopyPath');
const copySuccessMsg = document.getElementById('copySuccessMsg');

// Initialize
window.addEventListener('DOMContentLoaded', () => {
    initPresetButtons();
    initControls();
    loadMatrix(PRESETS.vd1);
});

function initPresetButtons() {
    const buttons = document.querySelectorAll('.btn-preset');
    buttons.forEach(btn => {
        btn.addEventListener('click', (e) => {
            buttons.forEach(b => b.classList.remove('active'));
            btn.classList.add('active');

            const presetKey = btn.dataset.preset;
            if (presetKey === 'random') {
                // Show custom size controls and hide preset notice
                gridSizeControls.style.display = 'flex';
                presetNotice.style.display = 'none';

                const rows = Math.min(10, Math.max(1, parseInt(inputRows.value) || 4));
                const cols = Math.min(10, Math.max(1, parseInt(inputCols.value) || 5));
                const pattern = selectPattern ? selectPattern.value : 'challenging';
                const mat = generateChallengingMatrix(rows, cols, pattern);
                loadMatrix(mat);
            } else if (PRESETS[presetKey]) {
                // Hide custom size controls for fixed presets
                gridSizeControls.style.display = 'none';
                presetNotice.style.display = 'flex';
                loadMatrix(PRESETS[presetKey]);
            }
        });
    });
}

function initControls() {
    btnApplySize.addEventListener('click', () => {
        const rows = Math.min(10, Math.max(1, parseInt(inputRows.value) || 4));
        const cols = Math.min(10, Math.max(1, parseInt(inputCols.value) || 5));
        inputRows.value = rows;
        inputCols.value = cols;

        const pattern = selectPattern ? selectPattern.value : 'challenging';
        const newC = generateChallengingMatrix(rows, cols, pattern);
        loadMatrix(newC);
    });

    if (selectPattern) {
        selectPattern.addEventListener('change', () => {
            const rows = Math.min(10, Math.max(1, parseInt(inputRows.value) || 4));
            const cols = Math.min(10, Math.max(1, parseInt(inputCols.value) || 5));
            const newC = generateChallengingMatrix(rows, cols, selectPattern.value);
            loadMatrix(newC);
        });
    }

    btnSolve.addEventListener('click', () => {
        stopAnimation();
        solveInstant();
    });

    btnStepByStep.addEventListener('click', () => {
        stopAnimation();
        startStepByStepAnimation();
    });

    btnReset.addEventListener('click', () => {
        stopAnimation();
        clearVisuals();
    });

    rangeSpeed.addEventListener('input', (e) => {
        state.stepSpeed = parseInt(e.target.value);
        speedDisplay.textContent = `${state.stepSpeed}ms`;
    });

    btnCopyPath.addEventListener('click', () => {
        if (!state.path || state.path.length === 0) return;
        const text = `tong=${resultTotalSum.textContent}; duong=[${state.path.map(p => `(${p.r}, ${p.c})`).join(', ')}]`;
        navigator.clipboard.writeText(text).then(() => {
            copySuccessMsg.style.display = 'inline';
            setTimeout(() => {
                copySuccessMsg.style.display = 'none';
            }, 2000);
        });
    });
}

function loadMatrix(matrix) {
    stopAnimation();
    state.m = matrix.length;
    state.n = matrix[0].length;
    state.C = matrix.map(row => [...row]);
    
    inputRows.value = state.m;
    inputCols.value = state.n;

    renderGridC();
    renderEmptyGridF();
    clearVisuals();
}

/**
 * Sinh ma trận thách thức & khó nhằn theo kiểu mẫu
 */
function generateChallengingMatrix(rows, cols, pattern = 'challenging') {
    const mat = Array.from({ length: rows }, () => Array(cols).fill(0));

    if (pattern === 'zigzag') {
        // Mê cung ZigZag với tường bẫy 99 ở các hàng xen kẽ
        for (let i = 0; i < rows; ++i) {
            for (let j = 0; j < cols; ++j) {
                if (i % 2 === 1 && j < cols - 1) {
                    mat[i][j] = 99; // Bẫy cực lớn
                } else if (i % 2 === 0 && i > 0 && j > 0) {
                    mat[i][j] = (Math.random() < 0.6) ? 88 : Math.floor(Math.random() * 8) + 1;
                } else {
                    mat[i][j] = Math.floor(Math.random() * 6) + 1;
                }
            }
        }
        mat[0][0] = Math.floor(Math.random() * 3) + 1;
        mat[rows - 1][cols - 1] = Math.floor(Math.random() * 3) + 1;
    } else if (pattern === 'challenging') {
        // Thách thức bẫy số: Tạo đường đi bí mật chi phí thấp (1-5), xung quanh rải bẫy 40-99 và bẫy cám dỗ
        // 1. Rải số ngẫu nhiên từ 30 đến 95
        for (let i = 0; i < rows; ++i) {
            for (let j = 0; j < cols; ++j) {
                mat[i][j] = Math.floor(Math.random() * 65) + 30; // 30 đến 94
            }
        }

        // 2. Tạo một đường đi ngẫu nhiên từ (0,0) đến (rows-1, cols-1) với trọng số nhỏ 1-6
        let r = 0, c = 0;
        mat[r][c] = Math.floor(Math.random() * 3) + 1;
        while (r < rows - 1 || c < cols - 1) {
            if (r === rows - 1) {
                c++;
            } else if (c === cols - 1) {
                r++;
            } else {
                if (Math.random() < 0.5) r++;
                else c++;
            }
            mat[r][c] = Math.floor(Math.random() * 6) + 1;
        }

        // 3. Thêm một vài ô số 0 hoặc 1 cám dỗ ở các vị trí chết (dẫn đến ngõ cụt 99)
        for (let i = 0; i < Math.min(3, rows * cols / 4); ++i) {
            const randR = Math.floor(Math.random() * rows);
            const randC = Math.floor(Math.random() * cols);
            if (mat[randR][randC] > 10) {
                mat[randR][randC] = Math.floor(Math.random() * 2); // 0 hoặc 1
            }
        }
    } else if (pattern === 'varied') {
        // Đa dạng ngẫu nhiên 0 đến 50
        for (let i = 0; i < rows; ++i) {
            for (let j = 0; j < cols; ++j) {
                mat[i][j] = Math.floor(Math.random() * 51);
            }
        }
    } else {
        // Số nhỏ 1 đến 9
        for (let i = 0; i < rows; ++i) {
            for (let j = 0; j < cols; ++j) {
                mat[i][j] = Math.floor(Math.random() * 9) + 1;
            }
        }
    }

    return mat;
}

function renderGridC() {
    gridC.innerHTML = '';
    gridC.style.gridTemplateColumns = `repeat(${state.n}, 64px)`;

    for (let i = 0; i < state.m; ++i) {
        for (let j = 0; j < state.n; ++j) {
            const cell = document.createElement('div');
            cell.className = 'cell';
            cell.id = `cell_C_${i}_${j}`;

            if (i === 0 && j === 0) cell.classList.add('start-cell');
            if (i === state.m - 1 && j === state.n - 1) cell.classList.add('end-cell');

            const coord = document.createElement('span');
            coord.className = 'cell-coord';
            coord.textContent = `${i + 1},${j + 1}`;

            const input = document.createElement('input');
            input.type = 'number';
            input.className = 'cell-input';
            input.min = '0';
            input.max = '99';
            input.value = state.C[i][j];

            input.addEventListener('change', (e) => {
                let val = parseInt(e.target.value);
                if (isNaN(val) || val < 0) val = 0;
                if (val > 99) val = 99;
                e.target.value = val;
                state.C[i][j] = val;
                clearVisuals();
            });

            cell.appendChild(coord);
            cell.appendChild(input);
            gridC.appendChild(cell);
        }
    }
}

function renderEmptyGridF() {
    gridF.innerHTML = '';
    gridF.style.gridTemplateColumns = `repeat(${state.n}, 64px)`;

    for (let i = 0; i < state.m; ++i) {
        for (let j = 0; j < state.n; ++j) {
            const cell = document.createElement('div');
            cell.className = 'cell';
            cell.id = `cell_F_${i}_${j}`;

            const coord = document.createElement('span');
            coord.className = 'cell-coord';
            coord.textContent = `${i + 1},${j + 1}`;

            const val = document.createElement('span');
            val.className = 'cell-value';
            val.textContent = '-';

            cell.appendChild(coord);
            cell.appendChild(val);
            gridF.appendChild(cell);
        }
    }
}

function clearVisuals() {
    stepStatusIndicator.textContent = 'Sẵn sàng';
    stepStatusIndicator.classList.remove('active');
    explanationText.innerHTML = 'Nhấn <strong>"Giải ngay"</strong> hoặc <strong>"Chạy từng bước"</strong> để bắt đầu mô phỏng.';
    resultTotalSum.textContent = '--';
    resultStepCount.textContent = '--';
    resultOptSpace.textContent = '--';
    resultPathDisplay.textContent = 'Chưa thực thi';

    // Remove path classes in C
    document.querySelectorAll('#gridC .cell').forEach(c => c.classList.remove('in-path', 'calc-current', 'calc-compare'));
    
    // Clear F table values and classes
    for (let i = 0; i < state.m; ++i) {
        for (let j = 0; j < state.n; ++j) {
            const cellF = document.getElementById(`cell_F_${i}_${j}`);
            if (cellF) {
                cellF.className = 'cell';
                const val = cellF.querySelector('.cell-value');
                if (val) val.textContent = '-';
                const arrow = cellF.querySelector('.from-dir-arrow');
                if (arrow) arrow.remove();
            }
        }
    }
}

// Full DP Calculation
function computeDP() {
    const m = state.m;
    const n = state.n;
    const f = Array.from({ length: m }, () => Array(n).fill(0));
    const fromDir = Array.from({ length: m }, () => Array(n).fill(''));

    // Step 1: Start cell
    f[0][0] = state.C[0][0];
    fromDir[0][0] = 'start';

    // Step 2a: First row (from left)
    for (let j = 1; j < n; ++j) {
        f[0][j] = f[0][j - 1] + state.C[0][j];
        fromDir[0][j] = 'left';
    }

    // Step 2b: First column (from top)
    for (let i = 1; i < m; ++i) {
        f[i][0] = f[i - 1][0] + state.C[i][0];
        fromDir[i][0] = 'top';
    }

    // Step 3: Inner cells
    for (let i = 1; i < m; ++i) {
        for (let j = 1; j < n; ++j) {
            if (f[i - 1][j] <= f[i][j - 1]) {
                f[i][j] = f[i - 1][j] + state.C[i][j];
                fromDir[i][j] = 'top';
            } else {
                f[i][j] = f[i][j - 1] + state.C[i][j];
                fromDir[i][j] = 'left';
            }
        }
    }

    // Backtrack route
    const path = [];
    let curI = m - 1;
    let curJ = n - 1;
    path.push({ r: curI + 1, c: curJ + 1 });

    while (curI > 0 || curJ > 0) {
        if (curI === 0) {
            curJ--;
        } else if (curJ === 0) {
            curI--;
        } else {
            if (f[curI - 1][curJ] <= f[curI][curJ - 1]) {
                curI--;
            } else {
                curJ--;
            }
        }
        path.push({ r: curI + 1, c: curJ + 1 });
    }
    path.reverse();

    // 1-Row space optimized version calculation
    const dp1 = Array(n).fill(0);
    dp1[0] = state.C[0][0];
    for (let j = 1; j < n; ++j) dp1[j] = dp1[j - 1] + state.C[0][j];
    for (let i = 1; i < m; ++i) {
        dp1[0] += state.C[i][0];
        for (let j = 1; j < n; ++j) {
            dp1[j] = Math.min(dp1[j], dp1[j - 1]) + state.C[i][j];
        }
    }

    return { f, fromDir, path, opt1D: dp1[n - 1] };
}

// Instant Solve
function solveInstant() {
    clearVisuals();
    const result = computeDP();
    state.f = result.f;
    state.fromDir = result.fromDir;
    state.path = result.path;

    // Fill F table immediately
    for (let i = 0; i < state.m; ++i) {
        for (let j = 0; j < state.n; ++j) {
            const cellF = document.getElementById(`cell_F_${i}_${j}`);
            if (cellF) {
                cellF.querySelector('.cell-value').textContent = state.f[i][j];
                addDirectionArrow(cellF, state.fromDir[i][j]);
            }
        }
    }

    // Highlight path in both grids
    highlightPath();

    // Update Dashboard
    const total = state.f[state.m - 1][state.n - 1];
    resultTotalSum.textContent = total;
    resultStepCount.textContent = state.path.length;
    resultOptSpace.textContent = result.opt1D;
    resultPathDisplay.textContent = `duong=[${state.path.map(p => `(${p.r}, ${p.c})`).join(', ')}]`;

    stepStatusIndicator.textContent = 'Hoàn thành';
    stepStatusIndicator.classList.add('active');
    explanationText.innerHTML = `Đã tìm thấy phương án tối ưu! Tổng chi phí nhỏ nhất: <code>${total}</code> qua <code>${state.path.length}</code> ô.`;
}

function addDirectionArrow(cellF, dir) {
    let arrowChar = '';
    if (dir === 'left') arrowChar = '←';
    else if (dir === 'top') arrowChar = '↑';
    else if (dir === 'start') arrowChar = '★';

    if (arrowChar) {
        const arrow = document.createElement('span');
        arrow.className = 'from-dir-arrow';
        arrow.textContent = arrowChar;
        cellF.appendChild(arrow);
    }
}

function highlightPath() {
    state.path.forEach(pt => {
        const r = pt.r - 1;
        const c = pt.c - 1;
        const cellC = document.getElementById(`cell_C_${r}_${c}`);
        const cellF = document.getElementById(`cell_F_${r}_${c}`);
        if (cellC) cellC.classList.add('in-path');
        if (cellF) cellF.classList.add('in-path');
    });
}

// Step by Step Animation
function startStepByStepAnimation() {
    clearVisuals();
    const result = computeDP();
    state.f = result.f;
    state.fromDir = result.fromDir;
    state.path = result.path;
    state.animationRunning = true;
    stepStatusIndicator.classList.add('active');

    // Build queue of cells to fill in row-major order
    const queue = [];
    for (let i = 0; i < state.m; ++i) {
        for (let j = 0; j < state.n; ++j) {
            queue.push({ i, j });
        }
    }

    let qIdx = 0;

    function step() {
        if (!state.animationRunning) return;

        // Clear previous cell highlights
        document.querySelectorAll('.cell').forEach(c => c.classList.remove('calc-current', 'calc-compare'));

        if (qIdx < queue.length) {
            const { i, j } = queue[qIdx];
            stepStatusIndicator.textContent = `Đang tính ô (${i + 1}, ${j + 1})`;

            const cellC = document.getElementById(`cell_C_${i}_${j}`);
            const cellF = document.getElementById(`cell_F_${i}_${j}`);

            cellC.classList.add('calc-current');
            cellF.classList.add('calc-current');

            const valC = state.C[i][j];
            const valF = state.f[i][j];

            if (i === 0 && j === 0) {
                // Start
                explanationText.innerHTML = `<strong>Ô xuất phát (1, 1):</strong> <code>f[1, 1] = C[1, 1] = ${valC}</code>.`;
            } else if (i === 0) {
                // First row
                const leftF = document.getElementById(`cell_F_${i}_${j - 1}`);
                if (leftF) leftF.classList.add('calc-compare');
                explanationText.innerHTML = `<strong>Hàng đầu (chỉ đi sang phải):</strong> <code>f[1, ${j + 1}] = f[1, ${j}] + C[1, ${j + 1}] = ${state.f[0][j - 1]} + ${valC} = ${valF}</code>.`;
            } else if (j === 0) {
                // First column
                const topF = document.getElementById(`cell_F_${i - 1}_${j}`);
                if (topF) topF.classList.add('calc-compare');
                explanationText.innerHTML = `<strong>Cột đầu (chỉ đi xuống dưới):</strong> <code>f[${i + 1}, 1] = f[${i}, 1] + C[${i + 1}, 1] = ${state.f[i - 1][0]} + ${valC} = ${valF}</code>.`;
            } else {
                // Inner cell
                const topF = document.getElementById(`cell_F_${i - 1}_${j}`);
                const leftF = document.getElementById(`cell_F_${i}_${j - 1}`);
                if (topF) topF.classList.add('calc-compare');
                if (leftF) leftF.classList.add('calc-compare');

                const topVal = state.f[i - 1][j];
                const leftVal = state.f[i][j - 1];
                const minVal = Math.min(topVal, leftVal);
                const dir = (topVal <= leftVal) ? 'ô trên' : 'ô trái';

                explanationText.innerHTML = `<strong>Ô nội bộ (${i + 1}, ${j + 1}):</strong> So sánh ô trên (<code>${topVal}</code>) và ô trái (<code>${leftVal}</code>). Chọn nhỏ nhất từ ${dir} là <code>${minVal}</code> + chi phí ô hiện tại <code>${valC}</code> = <code>${valF}</code>.`;
            }

            // Fill cell value
            cellF.querySelector('.cell-value').textContent = valF;
            addDirectionArrow(cellF, state.fromDir[i][j]);

            qIdx++;
            state.timerId = setTimeout(step, state.stepSpeed);
        } else {
            // Table filled, now animate backtracking
            animateBacktracking(0);
        }
    }

    step();
}

function animateBacktracking(pathIdx) {
    if (!state.animationRunning) return;

    if (pathIdx < state.path.length) {
        stepStatusIndicator.textContent = `Truy vết ô ${pathIdx + 1}/${state.path.length}`;
        const pt = state.path[pathIdx];
        const r = pt.r - 1;
        const c = pt.c - 1;

        const cellC = document.getElementById(`cell_C_${r}_${c}`);
        const cellF = document.getElementById(`cell_F_${r}_${c}`);
        if (cellC) cellC.classList.add('in-path');
        if (cellF) cellF.classList.add('in-path');

        explanationText.innerHTML = `<strong>Truy vết đường đi:</strong> Đi qua ô <code>(${pt.r}, ${pt.c})</code> với chi phí tích lũy <code>f = ${state.f[r][c]}</code>.`;

        state.timerId = setTimeout(() => {
            animateBacktracking(pathIdx + 1);
        }, Math.max(150, state.stepSpeed * 0.7));
    } else {
        // Complete
        state.animationRunning = false;
        stepStatusIndicator.textContent = 'Hoàn tất';
        const total = state.f[state.m - 1][state.n - 1];
        resultTotalSum.textContent = total;
        resultStepCount.textContent = state.path.length;
        resultOptSpace.textContent = total;
        resultPathDisplay.textContent = `duong=[${state.path.map(p => `(${p.r}, ${p.c})`).join(', ')}]`;
        explanationText.innerHTML = `🎉 <strong>Hoàn thành xuất sắc!</strong> Tổng chi phí nhỏ nhất: <code>${total}</code>. Đường đi tối ưu gồm <code>${state.path.length}</code> bước.`;
    }
}

function stopAnimation() {
    state.animationRunning = false;
    if (state.timerId) {
        clearTimeout(state.timerId);
        state.timerId = null;
    }
}

// ==========================================================================
// CÁC TÍNH NĂNG NÂNG CAO MỞ RỘNG
// ==========================================================================

// 1. Thuật toán Tham lam (Greedy)
function solveGreedy() {
    let i = 0, j = 0;
    let sum = state.C[0][0];
    const path = [{ r: 1, c: 1 }];

    while (i < state.m - 1 || j < state.n - 1) {
        if (i === state.m - 1) {
            j++;
        } else if (j === state.n - 1) {
            i++;
        } else {
            if (state.C[i][j + 1] < state.C[i + 1][j]) {
                j++;
            } else {
                i++;
            }
        }
        sum += state.C[i][j];
        path.push({ r: i + 1, c: j + 1 });
    }
    return { sum, path };
}

// 2. Thuật toán Dijkstra trên lưới
function solveDijkstra() {
    const m = state.m;
    const n = state.n;
    const dist = Array.from({ length: m }, () => Array(n).fill(Infinity));
    const parent = Array.from({ length: m }, () => Array(n).fill(null));
    const visited = Array.from({ length: m }, () => Array(n).fill(false));

    dist[0][0] = state.C[0][0];

    for (let step = 0; step < m * n; step++) {
        let minDist = Infinity;
        let u = -1, v = -1;

        for (let r = 0; r < m; r++) {
            for (let c = 0; c < n; c++) {
                if (!visited[r][c] && dist[r][c] < minDist) {
                    minDist = dist[r][c];
                    u = r;
                    v = c;
                }
            }
        }

        if (u === -1 || (u === m - 1 && v === n - 1)) break;
        visited[u][v] = true;

        // Đi sang phải
        if (v + 1 < n && dist[u][v] + state.C[u][v + 1] < dist[u][v + 1]) {
            dist[u][v + 1] = dist[u][v] + state.C[u][v + 1];
            parent[u][v + 1] = { r: u, c: v };
        }
        // Đi xuống dưới
        if (u + 1 < m && dist[u][v] + state.C[u + 1][v] < dist[u + 1][v]) {
            dist[u + 1][v] = dist[u][v] + state.C[u + 1][v];
            parent[u + 1][v] = { r: u, c: v };
        }
    }

    const path = [];
    let cur = { r: m - 1, c: n - 1 };
    while (cur) {
        path.push({ r: cur.r + 1, c: cur.c + 1 });
        cur = parent[cur.r][cur.c];
    }
    path.reverse();

    return { sum: dist[m - 1][n - 1], path };
}

// 3. Tìm tất cả các đường đi tối ưu (DFS trên bảng f)
function findAllOptimalPaths() {
    if (!state.f || state.f.length === 0) return [];
    const allPaths = [];

    function dfs(i, j, currentPath) {
        if (allPaths.length >= 20) return;
        currentPath.push({ r: i + 1, c: j + 1 });

        if (i === 0 && j === 0) {
            allPaths.push([...currentPath].reverse());
            currentPath.pop();
            return;
        }

        if (i > 0 && j > 0) {
            const minVal = Math.min(state.f[i - 1][j], state.f[i][j - 1]);
            if (state.f[i - 1][j] === minVal) dfs(i - 1, j, currentPath);
            if (state.f[i][j - 1] === minVal) dfs(i, j - 1, currentPath);
        } else if (i > 0) {
            dfs(i - 1, j, currentPath);
        } else if (j > 0) {
            dfs(i, j - 1, currentPath);
        }

        currentPath.pop();
    }

    dfs(state.m - 1, state.n - 1, []);
    return allPaths;
}

// Cập nhật thẻ So sánh thuật toán
function updateAlgorithmComparison(dpTotal) {
    const greedy = solveGreedy();
    const dijkstra = solveDijkstra();

    const greedySumEl = document.getElementById('greedySum');
    const greedyOptStatusEl = document.getElementById('greedyOptStatus');
    const dpSumEl = document.getElementById('dpSum');
    const dijkstraSumEl = document.getElementById('dijkstraSum');

    if (greedySumEl) greedySumEl.textContent = greedy.sum;
    if (dpSumEl) dpSumEl.textContent = dpTotal;
    if (dijkstraSumEl) dijkstraSumEl.textContent = dijkstra.sum;

    if (greedyOptStatusEl) {
        if (greedy.sum === dpTotal) {
            greedyOptStatusEl.textContent = '✅ Trùng tối ưu';
            greedyOptStatusEl.className = 'status-tag tag-opt';
        } else {
            greedyOptStatusEl.textContent = '❌ Kém hơn (+ ' + (greedy.sum - dpTotal) + ')';
            greedyOptStatusEl.className = 'status-tag tag-subopt';
        }
    }
}

// Toggle Heatmap
let heatmapActive = false;
function toggleHeatmap() {
    heatmapActive = !heatmapActive;
    const btnHeatmap = document.getElementById('btnHeatmap');
    if (btnHeatmap) {
        btnHeatmap.classList.toggle('active', heatmapActive);
    }

    if (!state.f || state.f.length === 0) {
        solveInstant();
    }

    let minVal = Infinity, maxVal = -Infinity;
    for (let i = 0; i < state.m; i++) {
        for (let j = 0; j < state.n; j++) {
            minVal = Math.min(minVal, state.f[i][j]);
            maxVal = Math.max(maxVal, state.f[i][j]);
        }
    }

    const range = Math.max(1, maxVal - minVal);

    for (let i = 0; i < state.m; i++) {
        for (let j = 0; j < state.n; j++) {
            const cellF = document.getElementById(`cell_F_${i}_${j}`);
            if (!cellF) continue;
            cellF.classList.remove('heat-low', 'heat-mid', 'heat-high');

            if (heatmapActive) {
                const ratio = (state.f[i][j] - minVal) / range;
                if (ratio < 0.33) cellF.classList.add('heat-low');
                else if (ratio < 0.66) cellF.classList.add('heat-mid');
                else cellF.classList.add('heat-high');
            }
        }
    }
}

// Toggle Tất cả đường tối ưu
function toggleAllPaths() {
    const container = document.getElementById('allPathsContainer');
    const listEl = document.getElementById('allPathsList');
    if (!container || !listEl) return;

    if (container.style.display === 'none') {
        if (!state.f || state.f.length === 0) solveInstant();
        const paths = findAllOptimalPaths();
        listEl.innerHTML = '';

        paths.forEach((p, idx) => {
            const item = document.createElement('div');
            item.className = 'path-item';
            item.textContent = `Đường #${idx + 1}: [${p.map(pt => `(${pt.r}, ${pt.c})`).join(' → ')}]`;
            listEl.appendChild(item);
        });

        container.style.display = 'block';
    } else {
        container.style.display = 'none';
    }
}

// Xuất CSV ma trận và kết quả
function exportCSV() {
    if (!state.f || state.f.length === 0) solveInstant();
    let csv = "DATA MA TRAN BAN DAU C[i][j]\n";
    for (let i = 0; i < state.m; i++) {
        csv += state.C[i].join(",") + "\n";
    }
    csv += "\nBANG PHUONG AN QUY HOACH DONG f[i][j]\n";
    for (let i = 0; i < state.m; i++) {
        csv += state.f[i].join(",") + "\n";
    }
    csv += "\nKET QUA DUONG DI TOI UU\n";
    csv += `Tong chi phi: ${state.f[state.m - 1][state.n - 1]}\n`;
    csv += `Duong di: ${state.path.map(p => `(${p.r};${p.c})`).join(" -> ")}\n`;

    const blob = new Blob([csv], { type: 'text/csv;charset=utf-8;' });
    const link = document.createElement("a");
    link.href = URL.createObjectURL(blob);
    link.download = `DT053_NgoLeTanNhan_${state.m}x${state.n}.csv`;
    link.click();
}

// Gán sự kiện khi trang đã tải
window.addEventListener('DOMContentLoaded', () => {
    const btnHeatmap = document.getElementById('btnHeatmap');
    if (btnHeatmap) btnHeatmap.addEventListener('click', toggleHeatmap);

    const btnAllPaths = document.getElementById('btnAllPaths');
    if (btnAllPaths) btnAllPaths.addEventListener('click', toggleAllPaths);

    const btnExportCSV = document.getElementById('btnExportCSV');
    if (btnExportCSV) btnExportCSV.addEventListener('click', exportCSV);
});

// Hook vào hàm solveInstant để tự động cập nhật so sánh giải thuật
const originalSolveInstant = solveInstant;
solveInstant = function() {
    originalSolveInstant();
    if (state.f && state.f.length > 0) {
        updateAlgorithmComparison(state.f[state.m - 1][state.n - 1]);
    }
};
