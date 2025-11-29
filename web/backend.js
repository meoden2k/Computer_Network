let ws = new WebSocket("ws://192.168.2.152:9000"); // IP server

ws.onopen = () => {
    log("Connected!");
    
};

ws.onmessage = (e) => log("Server replied: " + e.data);

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

let startApp = document.getElementById("StartApp");
function StartApp(){
        if (ws.readyState === WebSocket.OPEN){
        ws.send("list_apps");
    }
    else {
        log("WebSocket chưa kết nối xong.");
    }
}