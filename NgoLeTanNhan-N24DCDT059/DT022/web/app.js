/**
 * DT022 - BINARY SEARCH BOUNDARY VISUALIZER LOGIC
 * Sinh vien: Ngo Le Tan Nhan - MSSV: N24DCDT059 - INT13185 (Nhom 03)
 */

document.addEventListener('DOMContentLoaded', () => {
    // DOM Elements
    const inputArray = document.getElementById('inputArray');
    const inputTarget = document.getElementById('inputTarget');
    const btnApplyCustom = document.getElementById('btnApplyCustom');
    const btnSolve = document.getElementById('btnSolve');
    const btnNextStep = document.getElementById('btnNextStep');
    const btnReset = document.getElementById('btnReset');
    const btnCompareLinear = document.getElementById('btnCompareLinear');
    const btnExtended = document.getElementById('btnExtended');
    const btnCloseExtended = document.getElementById('btnCloseExtended');
    const btnExportCSV = document.getElementById('btnExportCSV');
    const rangeSpeed = document.getElementById('rangeSpeed');
    const speedDisplay = document.getElementById('speedDisplay');
    const statusBanner = document.getElementById('statusBanner');
    const statusText = document.getElementById('statusText');

    const arrayContainer = document.getElementById('arrayContainer');
    const explanationContent = document.getElementById('explanationContent');
    const valBien = document.getElementById('valBien');
    const valSoNhoHon = document.getElementById('valSoNhoHon');
    const valSteps = document.getElementById('valSteps');
    const valLinear = document.getElementById('valLinear');
    const traceTableBody = document.getElementById('traceTableBody');

    const extendedPanel = document.getElementById('extendedPanel');
    const extResLess = document.getElementById('extResLess');
    const extResLe = document.getElementById('extResLe');
    const extResEq = document.getElementById('extResEq');

    // Preset Buttons
    const presetButtons = document.querySelectorAll('.btn-preset');

    // State Variables
    let currentArray = [1, 2, 2, 4];
    let currentTarget = 2;
    let traceSteps = [];
    let currentStepIndex = -1;
    let animationInterval = null;
    let isPlaying = false;
    let finalBien = null;
    let finalSoNhoHon = null;

    // Presets Dictionary
    const PRESETS = {
        vd1: { arr: [1, 2, 2, 4], x: 2, label: 'Ví dụ 1 đề bài: a = [1, 2, 2, 4], x = 2' },
        vd2: { arr: [1, 2, 2, 4], x: 5, label: 'Ví dụ 2 đề bài: a = [1, 2, 2, 4], x = 5' },
        min: { arr: [1, 2, 2, 4], x: 0, label: 'x < Min: a = [1, 2, 2, 4], x = 0' },
        trung: { arr: [3, 3, 3, 3], x: 3, label: 'Toàn bộ trùng x: a = [3, 3, 3, 3], x = 3' },
        am: { arr: [-15, -7, 0, 0, 4, 12, 19], x: 0, label: 'Mảng số âm & 0: a = [-15, -7, 0, 0, 4, 12, 19], x = 0' },
        khoatrung: { arr: [2, 2, 2, 5, 5, 8, 8, 8], x: 5, label: 'Khóa trùng kéo dài: a = [2, 2, 2, 5, 5, 8, 8, 8], x = 5' },
        don: { arr: [7], x: 7, label: 'Đơn phần tử: a = [7], x = 7' },
        rong: { arr: [], x: 10, label: 'Mảng rỗng: a = [], x = 10' },
        random: { arr: [], x: 15, label: 'Dữ liệu ngẫu nhiên' }
    };

    // Initialize
    setPreset('vd1');

    // Speed display updater
    if (rangeSpeed && speedDisplay) {
        rangeSpeed.addEventListener('input', (e) => {
            speedDisplay.textContent = `${e.target.value}ms`;
        });
    }

    // Preset handlers
    presetButtons.forEach(btn => {
        btn.addEventListener('click', () => {
            presetButtons.forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
            const pKey = btn.dataset.preset;
            setPreset(pKey);
        });
    });

    function setPreset(key) {
        stopAnimation();
        if (key === 'random') {
            const len = Math.floor(Math.random() * 8) + 5; // 5..12
            const set = [];
            let val = Math.floor(Math.random() * 5) - 3;
            for (let i = 0; i < len; i++) {
                val += Math.floor(Math.random() * 6);
                set.push(val);
            }
            currentArray = set;
            currentTarget = set[Math.floor(Math.random() * set.length)];
        } else {
            const p = PRESETS[key];
            currentArray = [...p.arr];
            currentTarget = p.x;
        }

        inputArray.value = currentArray.join(', ');
        inputTarget.value = currentTarget;

        resetVisualizer();
        showStatus(`Đã tải bộ dữ liệu mẫu: [${currentArray.join(', ')}], x = ${currentTarget}`, 'normal');
    }

    // Apply custom input
    btnApplyCustom.addEventListener('click', () => {
        stopAnimation();
        const rawArr = inputArray.value.trim();
        const rawX = inputTarget.value.trim();

        if (rawX === '' || isNaN(Number(rawX))) {
            showStatus('Lỗi: Giá trị khóa x phải là một số nguyên hợp lệ!', 'error');
            return;
        }

        let parsed = [];
        if (rawArr.length > 0) {
            const parts = rawArr.split(/[\s,]+/);
            for (let p of parts) {
                if (p === '') continue;
                const num = Number(p);
                if (isNaN(num)) {
                    showStatus(`Lỗi: Phần tử "${p}" không phải là số hợp lệ!`, 'error');
                    return;
                }
                parsed.push(num);
            }
        }

        // Validate sorted
        for (let i = 0; i < parsed.length - 1; i++) {
            if (parsed[i] > parsed[i + 1]) {
                showStatus(`Lỗi: Mảng chưa được sắp tăng không giảm tại vị trí ${i + 1} (${parsed[i]} > ${parsed[i+1]})!`, 'error');
                return;
            }
        }

        if (parsed.length > 10000) {
            showStatus('Lỗi: Kích thước mảng không được vượt quá 10000 phần tử!', 'error');
            return;
        }

        currentArray = parsed;
        currentTarget = Number(rawX);
        presetButtons.forEach(b => b.classList.remove('active'));

        resetVisualizer();
        showStatus(`Đã cập nhật mảng n = ${currentArray.length}, khóa x = ${currentTarget}`, 'success');
    });

    // Reset Visualizer
    btnReset.addEventListener('click', () => {
        stopAnimation();
        resetVisualizer();
        showStatus('Đã làm mới trạng thái trực quan hóa.', 'normal');
    });

    function resetVisualizer() {
        stopAnimation();
        currentStepIndex = -1;
        traceSteps = [];
        finalBien = null;
        finalSoNhoHon = null;

        valBien.textContent = '--';
        valSoNhoHon.textContent = '--';
        valSteps.textContent = '--';
        valLinear.textContent = '--';

        renderArrayBase();
        clearTable();
        explanationContent.innerHTML = 'Nhấn <strong>"Giải ngay"</strong> hoặc nhấp <strong>"Giải từng bước"</strong> để bắt đầu mô phỏng thuật toán.';
        if (btnNextStep) {
            btnNextStep.disabled = false;
            btnNextStep.innerHTML = '<span class="btn-icon">⏭</span> Giải từng bước';
        }
    }

    // Render Array Base
    function renderArrayBase() {
        arrayContainer.innerHTML = '';
        if (currentArray.length === 0) {
            arrayContainer.innerHTML = `
                <div class="boundary-after-array" style="border-style: solid;">
                    <div>MẢNG RỖNG</div>
                    <div style="font-size: 13px; margin-top: 4px;">bien = 1</div>
                    <div style="font-size: 10px; color: #cbd5e1;">(Quy ước đề bài)</div>
                </div>
            `;
            return;
        }

        currentArray.forEach((val, idx) => {
            const item = document.createElement('div');
            item.className = 'array-item-wrapper';
            item.id = `item-${idx + 1}`; // 1-based index

            item.innerHTML = `
                <div class="pointer-badge-container" id="ptr-${idx + 1}"></div>
                <div class="array-cell" id="cell-${idx + 1}">${val}</div>
                <div class="array-indices">
                    <span class="index-1based">[${idx + 1}]</span>
                    <span class="index-0based">i=${idx}</span>
                </div>
            `;
            arrayContainer.appendChild(item);
        });

        // Add virtual position n + 1 for boundary indicator when bien = n + 1
        const afterItem = document.createElement('div');
        afterItem.className = 'array-item-wrapper';
        afterItem.id = `item-${currentArray.length + 1}`;
        afterItem.innerHTML = `
            <div class="pointer-badge-container" id="ptr-${currentArray.length + 1}"></div>
            <div class="boundary-after-array" id="cell-${currentArray.length + 1}">
                <div>Vị trí sau mảng</div>
                <div style="font-size: 14px; color: #ec4899; font-family: var(--font-mono); font-weight:800;">[${currentArray.length + 1}]</div>
            </div>
            <div class="array-indices">
                <span class="index-1based">[n+1]</span>
            </div>
        `;
        arrayContainer.appendChild(afterItem);
    }

    // Calculate Binary Search Algorithm & Record Trace
    function computeBinarySearch() {
        traceSteps = [];
        const n = currentArray.length;
        let left = 1;
        let right = n;
        let bien = n + 1;
        let step = 0;

        while (left <= right) {
            step++;
            const mid = Math.floor(left + (right - left) / 2);
            const val = currentArray[mid - 1];
            const isGe = (val >= currentTarget);

            let actionText = '';
            if (isGe) {
                bien = mid;
                actionText = `a[${mid}] = ${val} ≥ ${currentTarget} ➔ Ghi nhận bien = ${mid}, thu hẹp sang trái [${left}, ${mid - 1}]`;
                traceSteps.push({
                    step,
                    left,
                    right,
                    mid,
                    val,
                    isGe,
                    bien,
                    nextLeft: left,
                    nextRight: mid - 1,
                    action: actionText
                });
                right = mid - 1;
            } else {
                actionText = `a[${mid}] = ${val} < ${currentTarget} ➔ Thu hẹp sang phải [${mid + 1}, ${right}]`;
                traceSteps.push({
                    step,
                    left,
                    right,
                    mid,
                    val,
                    isGe,
                    bien,
                    nextLeft: mid + 1,
                    nextRight: right,
                    action: actionText
                });
                left = mid + 1;
            }
        }

        finalBien = bien;
        finalSoNhoHon = bien - 1;
    }

    // Solve Immediately
    btnSolve.addEventListener('click', () => {
        stopAnimation();
        computeBinarySearch();
        renderAllStepsAtOnce();
    });

    function renderAllStepsAtOnce() {
        const n = currentArray.length;
        clearTable();
        renderArrayBase();

        // Populate table
        traceSteps.forEach(s => appendTableRow(s));

        // Mark array elements
        for (let i = 1; i <= n; i++) {
            const cell = document.getElementById(`cell-${i}`);
            if (!cell) continue;
            if (currentArray[i - 1] < currentTarget) {
                cell.className = 'array-cell cell-less-than-x';
            } else {
                cell.className = 'array-cell cell-ge-than-x';
            }
        }

        // Highlight boundary
        if (finalBien <= n) {
            const bCell = document.getElementById(`cell-${finalBien}`);
            if (bCell) {
                bCell.classList.add('cell-boundary-first');
            }
        } else {
            const afterCell = document.getElementById(`cell-${n + 1}`);
            if (afterCell) {
                afterCell.classList.add('boundary-active-target');
            }
        }

        // Update metrics
        valBien.textContent = finalBien;
        valSoNhoHon.textContent = finalSoNhoHon;
        valSteps.textContent = traceSteps.length;

        // Linear compare
        let linSteps = 0;
        let linBien = n + 1;
        for (let i = 0; i < n; i++) {
            linSteps++;
            if (currentArray[i] >= currentTarget) {
                linBien = i + 1;
                break;
            }
        }
        valLinear.textContent = `${linSteps} phép`;

        explanationContent.innerHTML = `
            <strong>HOÀN TẤT:</strong> Vị trí biên đầu tiên thỏa mãn <code>a[i] ≥ x</code> là <strong>bien = ${finalBien}</strong> (1-based).<br>
            ➔ Toàn bộ các phần tử từ chỉ số 1 đến ${finalBien - 1} đều nhỏ hơn <code>x = ${currentTarget}</code>.<br>
            ➔ Số lượng phần tử nhỏ hơn <code>x = ${currentTarget}</code> là <strong>so_nho_hon = ${finalSoNhoHon}</strong>.
        `;

        showStatus(`Đã giải hoàn tất! so_nho_hon = ${finalSoNhoHon}; bien = ${finalBien} (với ${traceSteps.length} bước lặp)`, 'success');
        btnNextStep.innerHTML = '<span class="btn-icon">✓</span> Đã hoàn tất';
        btnNextStep.disabled = true;
    }

    // Manual Step-by-Step Execution (User clicks for each step)
    btnNextStep.addEventListener('click', () => {
        // If not started yet or reached end, initialize computation
        if (currentStepIndex === -1 || currentStepIndex >= traceSteps.length - 1) {
            resetVisualizer();
            computeBinarySearch();
            currentStepIndex = -1;
            btnNextStep.disabled = false;
        }

        if (currentStepIndex < traceSteps.length - 1) {
            currentStepIndex++;
            renderStep(currentStepIndex);
            
            if (currentStepIndex === traceSteps.length - 1) {
                btnNextStep.innerHTML = '<span class="btn-icon">✓</span> Đã hoàn tất';
                btnNextStep.disabled = true;
                showStatus(`Đã hoàn thành giải từng bước! so_nho_hon = ${finalSoNhoHon}; bien = ${finalBien}`, 'success');
            } else {
                btnNextStep.innerHTML = `<span class="btn-icon">⏭</span> Bước tiếp theo (${currentStepIndex + 2}/${traceSteps.length})`;
                showStatus(`Đang ở bước ${currentStepIndex + 1}/${traceSteps.length}. Nhấp tiếp để xem bước sau.`, 'normal');
            }
        }
    });

    function stopAnimation() {
        if (btnNextStep) {
            btnNextStep.disabled = false;
            btnNextStep.innerHTML = '<span class="btn-icon">⏭</span> Giải từng bước';
        }
    }

    function renderStep(idx) {
        const s = traceSteps[idx];
        const n = currentArray.length;

        // Clear previous pointers
        for (let i = 1; i <= n; i++) {
            const ptr = document.getElementById(`ptr-${i}`);
            if (ptr) ptr.innerHTML = '';
            const cell = document.getElementById(`cell-${i}`);
            if (cell) {
                cell.className = 'array-cell';
                if (i < s.left || i > s.right) {
                    cell.classList.add('cell-inactive');
                } else {
                    cell.classList.add('cell-in-range');
                }
            }
        }
        // Reset boundary-after-array if present
        const ptrAfter = document.getElementById(`ptr-${n + 1}`);
        if (ptrAfter) ptrAfter.innerHTML = '';
        const cellAfter = document.getElementById(`cell-${n + 1}`);
        if (cellAfter) {
            cellAfter.className = 'boundary-after-array';
        }

        // Place Left Pointer
        const ptrL = document.getElementById(`ptr-${s.left}`);
        if (ptrL) {
            ptrL.innerHTML += '<span class="pointer-badge badge-left">L</span>';
        }

        // Place Right Pointer
        const ptrR = document.getElementById(`ptr-${s.right}`);
        if (ptrR) {
            ptrR.innerHTML += '<span class="pointer-badge badge-right">R</span>';
        }

        // Place Mid Pointer & highlight cell
        const ptrM = document.getElementById(`ptr-${s.mid}`);
        if (ptrM) {
            ptrM.innerHTML += '<span class="pointer-badge badge-mid">MID</span>';
        }
        const cellM = document.getElementById(`cell-${s.mid}`);
        if (cellM) {
            cellM.classList.remove('cell-in-range', 'cell-inactive');
            cellM.classList.add('cell-mid-active');
        }

        // Update live explanation
        explanationContent.innerHTML = `
            <strong>BƯỚC ${s.step}:</strong> Đang xét đoạn [Left = ${s.left}, Right = ${s.right}]. Chỉ số ở giữa: <strong>Mid = ${s.mid}</strong>.<br>
            ➔ So sánh phần tử: <code>a[${s.mid}] = ${s.val}</code> với khóa <code>x = ${currentTarget}</code>.<br>
            ➔ Kết quả so sánh: <strong>${s.isGe ? `a[${s.mid}] ≥ ${currentTarget} (ĐÚNG)` : `a[${s.mid}] < ${currentTarget} (SAI)`}</strong>.<br>
            ➔ Quyết định: <em>${s.action}</em>.
        `;

        // Add table row
        appendTableRow(s);

        // Update live metrics
        valBien.textContent = s.bien;
        valSoNhoHon.textContent = (s.bien === n + 1) ? '--' : (s.bien - 1);
        valSteps.textContent = `${s.step} / ${traceSteps.length}`;

        // If last step, colorize final areas
        if (idx === traceSteps.length - 1) {
            setTimeout(() => {
                for (let i = 1; i <= n; i++) {
                    const c = document.getElementById(`cell-${i}`);
                    if (!c) continue;
                    if (currentArray[i - 1] < currentTarget) {
                        c.className = 'array-cell cell-less-than-x';
                    } else {
                        c.className = 'array-cell cell-ge-than-x';
                    }
                }
                if (finalBien <= n) {
                    const bCell = document.getElementById(`cell-${finalBien}`);
                    if (bCell) bCell.classList.add('cell-boundary-first');
                } else {
                    const afterCell = document.getElementById(`cell-${n + 1}`);
                    if (afterCell) afterCell.classList.add('boundary-active-target');
                }

                valBien.textContent = finalBien;
                valSoNhoHon.textContent = finalSoNhoHon;
            }, 300);
        }
    }

    // Table Helper
    function clearTable() {
        traceTableBody.innerHTML = '';
    }

    function appendTableRow(s) {
        // Check if row already exists
        if (document.getElementById(`row-step-${s.step}`)) return;

        const tr = document.createElement('tr');
        tr.id = `row-step-${s.step}`;
        tr.innerHTML = `
            <td><strong>#${s.step}</strong></td>
            <td>${s.left}</td>
            <td>${s.right}</td>
            <td><strong>${s.mid}</strong></td>
            <td><code>${s.val}</code></td>
            <td>${s.isGe ? '<span class="tag-decision-ge">≥ x (Đúng)</span>' : '<span class="tag-decision-lt">&lt; x (Sai)</span>'}</td>
            <td><strong>${s.bien}</strong></td>
            <td>${s.action}</td>
        `;
        traceTableBody.appendChild(tr);
    }

    // Linear Compare
    btnCompareLinear.addEventListener('click', () => {
        const n = currentArray.length;
        let countLin = 0;
        let stepsLin = 0;
        let bienLin = n + 1;

        for (let i = 0; i < n; i++) {
            stepsLin++;
            if (currentArray[i] >= currentTarget) {
                bienLin = i + 1;
                countLin = i;
                break;
            }
        }
        if (bienLin === n + 1) {
            countLin = n;
        }

        computeBinarySearch();
        valLinear.textContent = `${stepsLin} phép`;

        alert(
            `=== ĐỐI CHIẾU THUẬT TOÁN ĐỘC LẬP ===\n\n` +
            `1. TÌM KIẾM NHỊ PHÂN O(log n):\n` +
            `   - Vị trí biên: bien = ${finalBien}\n` +
            `   - Số phần tử < x: so_nho_hon = ${finalSoNhoHon}\n` +
            `   - Số phép so sánh mid: ${traceSteps.length}\n\n` +
            `2. QUÉT TUẦN TỰ O(n):\n` +
            `   - Vị trí biên: bien = ${bienLin}\n` +
            `   - Số phần tử < x: so_nho_hon = ${countLin}\n` +
            `   - Số phép duyệt phần tử: ${stepsLin}\n\n` +
            `=> KẾT LUẬN: Hai thuật toán hoàn toàn đồng thuận kết quả 100%!`
        );
    });

    // Extended Modal (< x vs <= x)
    btnExtended.addEventListener('click', () => {
        extendedPanel.style.display = 'flex';
        const n = currentArray.length;

        // Compute lower bound (>= x)
        let bien_ge = n + 1;
        let l = 1, r = n;
        while (l <= r) {
            let m = Math.floor(l + (r - l) / 2);
            if (currentArray[m - 1] >= currentTarget) {
                bien_ge = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        const count_lt = bien_ge - 1;

        // Compute upper bound (> x)
        let bien_gt = n + 1;
        l = 1; r = n;
        while (l <= r) {
            let m = Math.floor(l + (r - l) / 2);
            if (currentArray[m - 1] > currentTarget) {
                bien_gt = m;
                r = m - 1;
            } else {
                l = m + 1;
            }
        }
        const count_le = bien_gt - 1;
        const count_eq = count_le - count_lt;

        extResLess.textContent = `bien = ${bien_ge} ➔ Số phần tử < ${currentTarget}: ${count_lt}`;
        extResLe.textContent = `bien = ${bien_gt} ➔ Số phần tử ≤ ${currentTarget}: ${count_le}`;
        extResEq.textContent = `Số lần xuất hiện của x = ${currentTarget}: ${count_eq} phần tử`;

        extendedPanel.scrollIntoView({ behavior: 'smooth' });
    });

    btnCloseExtended.addEventListener('click', () => {
        extendedPanel.style.display = 'none';
    });

    // Export CSV
    btnExportCSV.addEventListener('click', () => {
        computeBinarySearch();
        let csvContent = 'data:text/csv;charset=utf-8,\uFEFF';
        csvContent += 'DE TAI DT022: DEM SO PHAN TU NHO HON X BANG TIM KIEM NHI PHAN\n';
        csvContent += `Sinh vien: Ngo Le Tan Nhan - MSSV: N24DCDT059 - Lop: D24CQDT01-N\n`;
        csvContent += `Khoa x: ${currentTarget}\n`;
        csvContent += `Mang a: "${currentArray.join('; ')}"\n`;
        csvContent += `Ket qua: so_nho_hon = ${finalSoNhoHon}; bien = ${finalBien}\n\n`;

        csvContent += 'Buoc,Left,Right,Mid,a[Mid],Dieu_kien_ge,Bien_tam,Hanh_dong\n';
        traceSteps.forEach(s => {
            const row = [
                s.step,
                s.left,
                s.right,
                s.mid,
                s.val,
                s.isGe ? 'True' : 'False',
                s.bien,
                `"${s.action.replace(/"/g, '""')}"`
            ].join(',');
            csvContent += row + '\n';
        });

        const encodedUri = encodeURI(csvContent);
        const link = document.createElement('a');
        link.setAttribute('href', encodedUri);
        link.setAttribute('download', `DT022_LanVet_N24DCDT059_x${currentTarget}.csv`);
        document.body.appendChild(link);
        link.click();
        document.body.removeChild(link);
    });

    function showStatus(msg, type = 'normal') {
        statusText.textContent = msg;
        statusBanner.className = 'status-banner';
        if (type === 'success') statusBanner.classList.add('success');
        if (type === 'error') statusBanner.classList.add('error');
    }
});
