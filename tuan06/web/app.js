"use strict";
// Giao diện chỉ gửi lệnh và vẽ bản sao trạng thái nhận từ Python/Julia.
// Không cài thuật toán danh sách, ngăn xếp hoặc hàng đợi trong JavaScript.
const $ = (id) => document.getElementById(id);
const titles = {
  list: ["Danh sách liên kết đơn", "Dữ liệu nằm trong các nút; thứ tự được quyết định bởi liên kết ke."],
  stack: ["Ngăn xếp", "Đưa vào và lấy ra tại đỉnh. Phần tử vào sau cùng được lấy trước."],
  queue: ["Hàng đợi vòng", "Thêm cuối, lấy đầu. Phần tử vào trước được lấy trước; ô mảng được sử dụng lại theo vòng."],
  brackets: ["Kiểm tra dấu ngoặc", "Ngoặc đóng phải khớp với ngoặc mở gần nhất chưa đóng. Theo dõi từng ký tự bằng ngăn xếp."]
};
let tab = "list", state = null, token = "", busy = false, total = 0;
let history = [], trace = [], traceIndex = -1, timer = null;
let lastBefore = null, lastAfter = null;
const outcomes = {};
function node(tag, text, cls) {
  const e = document.createElement(tag);
  if (text !== undefined && text !== null) e.textContent = String(text);
  if (cls) e.className = cls;
  return e;
}
function format(x) {
  if (x === null || x === undefined) return "Không có giá trị (None / nothing)";
  if (typeof x === "boolean") return x ? "Đúng (true)" : "Sai (false)";
  return typeof x === "object" ? JSON.stringify(x) : String(x);
}
function inputInt(id) {
  const value = $(id).value.trim();
  if (!/^[+-]?\d+$/.test(value)) throw new Error("Cần nhập số nguyên, không dùng số thập phân.");
  const x = Number(value);
  if (!Number.isSafeInteger(x) || Math.abs(x) > 1000000) throw new Error("Số nguyên phải nằm trong [-1000000, 1000000].");
  return x;
}
function describe(s, kind=tab) {
  if (!s) return "Chưa thực hiện thao tác.";
  if (kind === "list") return "dau → " + (s.list.values.join(" → ") || "") + (s.list.n ? " → " : "") + "rỗng\nn = " + s.list.n;
  if (kind === "stack") return "Đáy → đỉnh: " + JSON.stringify(s.stack.values) + "\nSố phần tử = " + s.stack.n + "\nĐỉnh = " + format(s.stack.top);
  if (kind === "queue") return "Đầu → cuối: " + JSON.stringify(s.queue.values) + "\nMảng vật lý: " + JSON.stringify(s.queue.a) + "\ndau = " + s.queue.dau + "; so = " + s.queue.so + "; n = " + s.queue.n;
  return "Kiểm tra ngoặc sử dụng ngăn xếp cục bộ riêng; không thay đổi ba cấu trúc trong các thẻ khác.";
}
function stopTrace(){ if(timer){clearInterval(timer);timer=null;} $("trace-play").textContent="Tự chạy"; }
function switchTab(kind) {
  stopTrace(); tab = kind;
  for(const key of Object.keys(titles)) $("panel-"+key).hidden = key !== kind;
  document.querySelectorAll("[data-tab]").forEach(b => b.setAttribute("aria-pressed", String(b.dataset.tab === kind)));
  $("title").textContent=titles[kind][0]; $("intro").textContent=titles[kind][1];
  $("trace-card").hidden = kind !== "brackets" || !trace.length;
  showOutcome();
  render();
}
function showOutcome() {
  const a = outcomes[tab];
  lastBefore = a?.before || null; lastAfter = a?.state || null;
  feedback(a?.message || "Chọn một thao tác để bắt đầu.", !!a?.error);
  $("result").textContent = a ? (a.error ? "Thao tác không hoàn tất." : "Trả về: " + format(a.result)) : "Chưa có giá trị trả về.";
  $("steps").replaceChildren(...(a?.steps || ["Quan sát cấu trúc dữ liệu trước khi thực hiện.", "Giải thích vì sao kết quả thay đổi hoặc không thay đổi."]).map(t=>node("li",t)));
  $("before").textContent=describe(lastBefore); $("after").textContent=describe(lastAfter);
}
function render() {
  if (!state) return;
  $("language").textContent="Thuật toán: " + state.language;
  $("edition").textContent="Bản " + state.edition.toLowerCase();
  $("edition-note").textContent=state.edition === "Sinh viên" ? "Các thao tác cơ bản đã có mã. Bốn chức năng bài tập sẽ hoạt động sau khi hoàn thành tệp bài làm." : "Bản đáp án đã cài đặt cả bốn chức năng bài tập.";
  const v=$("visual");v.replaceChildren();$("queue-info").hidden=tab!=="queue";
  if(tab==="list"){
    $("count").textContent="n = "+state.list.n;
    if(!state.list.n) v.append(node("div","dau = rỗng. Danh sách chưa có nút.","empty"));
    else {
      const line=node("div",null,"chain");
      state.list.values.forEach((x,i)=>{const n=node("div",null,"node");n.append(node("strong",x),node("span","ke","link-field"));n.append(node("span",i===0?"dau / vị trí 1":"vị trí "+(i+1),"node-label"));line.append(n,node("span","→","edge"));});
      line.append(node("span","None / nothing","terminal"));v.append(line);
    }
    $("visual-note").textContent="Sơ đồ thứ tự logic, không phải địa chỉ RAM. Các nút có giá trị giống nhau vẫn là các đối tượng khác nhau.";
  }else if(tab==="stack"){
    $("count").textContent=state.stack.n+" phần tử";
    if(!state.stack.n) v.append(node("div","Ngăn xếp rỗng. Lấy hoặc xem đỉnh trả về None / nothing.","empty"));
    else {const tower=node("div",null,"stack-tower");[...state.stack.values].reverse().forEach((x,i)=>{const item=node("div",x,"stack-item"+(i===0?" top":""));if(i===0)item.append(node("span","ĐỈNH"));tower.append(item);});v.append(tower);}
    $("visual-note").textContent="Hình vẽ đặt đỉnh ở trên. Mảng lưu từ đáy tới đỉnh: "+JSON.stringify(state.stack.values)+".";
  }else if(tab==="queue"){
    const q=state.queue;$("count").textContent=q.so+" / "+q.n+" phần tử";
    const physical=node("div",null,"physical");
    q.a.forEach((x,i)=>{const active=q.active.includes(i), front=active&&i===q.dau;const c=node("div",null,"cell"+(active?" active":"")+(front?" front":""));c.append(node("em",front?"ĐẦU":active?"HỢP LỆ":"NGOÀI HÀNG"),node("span",x===null?"∅":x),node("small","ô logic "+i));physical.append(c);});v.append(physical,node("div","Đầu → cuối: "+(q.values.length?q.values.join(" → "):"rỗng"),"logical"));
    const metrics=node("div",null,"metrics");["dau = "+q.dau,"so = "+q.so,"n = "+q.n].forEach(x=>metrics.append(node("span",x)));v.append(metrics);
    $("queue-info").textContent=state.language==="Julia" ? "Julia: ô logic i được đọc/ghi bằng a[i + 1]. Ví dụ ô logic "+q.dau+" tương ứng a["+(q.dau+1)+"]." : "Python: ô logic i được đọc/ghi bằng a[i]. Ví dụ đầu hàng ở a["+q.dau+"].";
    $("visual-note").textContent="Ô ghi NGOÀI HÀNG không thuộc dữ liệu hợp lệ, kể cả khi còn số cũ. ∅ là ô chưa từng ghi. Thứ tự trong mảng vật lý có thể khác FIFO.";
  }else{
    $("count").textContent=trace.length?trace.length+" bước":"Chưa kiểm tra";
    if(traceIndex>=0 && trace[traceIndex]){
      const f=trace[traceIndex];v.append(node("div","Ký tự đang xét: "+(f.char||"Cuối chuỗi"),"logical"));
      const t=node("div",null,"stack-tower");
      if(!f.stack.length)t.append(node("div","Rỗng","empty"));
      else [...f.stack].reverse().forEach((x,i)=>{const item=node("div",x,"stack-item"+(i===0?" top":""));if(!i)item.append(node("span","ĐỈNH"));t.append(item);});
      v.append(t);
    }else v.append(node("div","Bấm Kiểm tra ngoặc để tạo lần vết.","empty"));
    $("visual-note").textContent="Đây là ngăn xếp riêng cho dấu ngoặc, không dùng dữ liệu trong thẻ Ngăn xếp. Vị trí đếm từ 1 theo ký tự.";
  }
}
function feedback(msg,error=false){$("feedback").textContent=msg;$("feedback").classList.toggle("error",error);}
async function connect(){
  try{
    const r=await fetch("/api/state",{cache:"no-store"});const d=await r.json();
    if(!r.ok||!d.ok)throw new Error(d.message||"Không nhận được trạng thái.");
    state=d.state;token=d.token;$("connection").hidden=true;render();
  }catch(e){$("connection").hidden=false;$("connection").textContent="Chưa kết nối được máy chủ. Chạy app.py hoặc app.jl, rồi mở địa chỉ http://127.0.0.1 được in trong terminal. Không mở index.html trực tiếp. "+e.message;}
}
function dataFor(op){
  const d={op};
  if(["list.prepend","list.append","list.find","list.insert","list.delete","list.count","list.delete_all"].includes(op))d.x=inputInt("list-x");
  if(op==="list.insert")d.target=inputInt("list-target");
  if(op==="stack.push")d.x=inputInt("stack-x");
  if(op==="queue.enqueue")d.x=inputInt("queue-x");
  if(op==="stack.pop_many")d.k=inputInt("stack-k");
  if(op==="queue.peek_k")d.k=inputInt("queue-k");
  if(op==="brackets.check")d.text=$("brackets-text").value;
  return d;
}
async function act(d){
  if(busy)return;stopTrace();busy=true;
  const actionTab = d.op === "all.reset" ? tab : d.op.split(".")[0];
  const buttons=[...document.querySelectorAll(".workspace button")];buttons.forEach(b=>b.disabled=true);
  try{
    if(!token)throw new Error("Chưa kết nối với máy chủ; bấm Đọc lại trạng thái.");
    const r=await fetch("/api/action",{method:"POST",headers:{"Content-Type":"application/json","X-Lab-Token":token},body:JSON.stringify(d)});
    const a=await r.json();
    if(!r.ok||!a.ok)throw new Error(a.message||"Thao tác không thành công.");
    state=a.state;
    if(d.op === "all.reset") {for(const key of Object.keys(outcomes)) delete outcomes[key];trace=[];traceIndex=-1;}
    outcomes[actionTab]=a;showOutcome();
    total++;history.push({number:total,request:d,result:a.result,message:a.message,before:a.before,state:a.state});if(history.length>200)history.shift();
    renderHistory();
    if(d.op==="brackets.check"){trace=a.trace;traceIndex=0;renderTrace();}
    render();
  }catch(e){outcomes[actionTab]={error:true,message:e.message,steps:["Kiểm tra dữ liệu nhập hoặc hàm trong tệp bài làm."]};showOutcome();}
  finally{busy=false;buttons.forEach(b=>b.disabled=false);if(tab === "brackets") renderTrace();}
}
function renderHistory(){
  $("history-count").textContent=total+" thao tác";
  $("history").replaceChildren(...[...history].reverse().map(x=>{const r=node("tr");r.append(node("td",x.number),node("td",x.request.op),node("td",x.message));return r;}));
}
function renderTrace(){
  $("trace-card").hidden=tab!=="brackets"||!trace.length;
  $("trace-counter").textContent=trace.length?"Bước "+(traceIndex+1)+" / "+trace.length:"";
  $("trace-prev").disabled=traceIndex<=0;$("trace-next").disabled=traceIndex>=trace.length-1;
  $("trace-note").textContent=trace[traceIndex]?.note||"";
  $("trace-body").replaceChildren(...trace.map((x,i)=>{const r=node("tr",null,(i===traceIndex?"trace-active ":"")+(!x.ok?"trace-error":""));r.append(node("td",x.char?x.pos:"Kết thúc"),node("td",x.char||"∅"),node("td",JSON.stringify(x.stack)),node("td",x.note));return r;}));render();
}
function safe(f){return ()=>{try{f();}catch(e){feedback(e.message,true);}};}
document.querySelectorAll("[data-tab]").forEach(b=>b.addEventListener("click",()=>switchTab(b.dataset.tab)));
document.querySelectorAll("[data-op]").forEach(b=>b.addEventListener("click",safe(()=>act(dataFor(b.dataset.op)))));
document.querySelectorAll("[data-example]").forEach(b=>b.addEventListener("click",()=>{$("brackets-text").value=b.dataset.example;act(dataFor("brackets.check"));}));
$("list-reset").onclick=safe(()=>{const raw=$("list-values").value.trim();const parts=raw?raw.split(",").map(x=>x.trim()):[];if(parts.some(x=>!/^[+-]?\d+$/.test(x)))throw new Error("Nhập các số nguyên cách nhau bởi dấu phẩy; không để phần tử trống.");act({op:"list.reset",values:parts.map(Number)});});
$("list-empty").onclick=()=>act({op:"list.reset",values:[]});
$("queue-reset").onclick=safe(()=>act({op:"queue.reset",capacity:inputInt("queue-capacity")}));
$("reset-all").onclick=()=>{if(confirm("Khôi phục dữ liệu mẫu cho cả ba cấu trúc?"))act({op:"all.reset"});};
$("refresh").onclick=connect;
$("export").onclick=()=>{const data={language:state?.language||"",edition:state?.edition||"",notice:"Nhật ký là dữ liệu thao tác, không phải chứng minh tác giả hoặc điểm số.",history};const blob=new Blob([JSON.stringify(data,null,2)],{type:"application/json"});const url=URL.createObjectURL(blob);const a=node("a");a.href=url;a.download="nhat_ky_chuong5.json";document.body.append(a);a.click();a.remove();setTimeout(()=>URL.revokeObjectURL(url),1000);};
$("trace-prev").onclick=()=>{stopTrace();if(traceIndex>0)traceIndex--;renderTrace();};
$("trace-next").onclick=()=>{stopTrace();if(traceIndex<trace.length-1)traceIndex++;renderTrace();};
$("trace-first").onclick=()=>{stopTrace();traceIndex=0;renderTrace();};
$("trace-play").onclick=()=>{if(timer){stopTrace();return;}if(traceIndex>=trace.length-1)traceIndex=0;$("trace-play").textContent="Dừng";timer=setInterval(()=>{if(traceIndex<trace.length-1){traceIndex++;renderTrace();}else stopTrace();},1200);};
connect();
