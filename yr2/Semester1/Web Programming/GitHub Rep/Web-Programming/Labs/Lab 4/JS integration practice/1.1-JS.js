function clickEventHandler(event) {
    event.target.style.color = "red";
}
function installEventHandler() {

    var clickableElement = document.getElementById("clickable");

    clickableElement.addEventListener("click", clickEventHandler);

    clickableElement.style.border = "1px solid black";
    
}