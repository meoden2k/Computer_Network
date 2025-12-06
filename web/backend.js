let ws = new WebSocket("ws://192.168.2.152:9000"); // IP server

ws.onopen = () => {
    log("Connected!");
    
};

// // Mỗi khi server gửi lại client bằng s->send thì
// // data được truyền vào "e"
// ws.onmessage = (e) => log("Server replied: " + e.data);

function sendHello() {
    if (ws.readyState === WebSocket.OPEN) {
        ws.send("Hello");
    } 
    else {
        log("WebSocket chưa kết nối xong.");
    }
}

function log(msg) {
    const logEl = document.getElementById("log");
    if (logEl) logEl.textContent += msg + "\n";
}

let btn = document.getElementById("btn_ListApp");
function listApp(){
    if (ws.readyState === WebSocket.OPEN){
        ws.send("list_apps");
    }
    else {
        log("WebSocket chưa kết nối xong.");
    }
}

function StartApp(event){

    event.preventDefault();

    const appNameInput = document.getElementById('startapp');
    const applicationName = appNameInput.value;

    if (ws.readyState === WebSocket.OPEN){
        ws.send("start_app:" + applicationName);
        appNameInput.value = ""
    }
    else {
        log("WebSocket chưa kết nối xong.");
    }
}
let startApp = document.getElementById("StartApp");
startApp.addEventListener('submit', StartApp);

function StopApp(event){
    event.preventDefault();

    const appNameInput = document.getElementById('stopapp');
    const applicationName = appNameInput.value;

    if (ws.readyState === WebSocket.OPEN){
        ws.send("stop_app:" + applicationName);
        appNameInput.value = ""
    }
    else {
        log("WebSocket chưa kết nối xong.");
    }
}
let stopApp = document.getElementById("StopApp");
stopApp.addEventListener('submit', StopApp)