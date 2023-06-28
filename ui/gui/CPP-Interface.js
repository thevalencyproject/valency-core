const ws = new WebSocket("localhost:3030");
ws.onmessage = (event) => {         // Wait for a message
    let i = event.data.slice(0, 3);     // Get the function index (sent by C++ server as first 3 digits)
    switch(i) {
    case "000":     // First Function
        receiveChangeColorButtonPressed(event.data);
        break;
    case "001":     // Second Function

        break;
    case "002":     // Third Function

        break;
    default:
        console.log("Invalid Server Message")
    }

    serverMessage = event.data;     // Set the serverMessage to the data that is sent back by the server
};


function sendChangeColorButtonPressed(input) {      // Sends data to the server after UI event happens
    let i = "000";
    var serverMessage;

    ws.send(i + input);
}
function receiveChangeColorButtonPressed(input) {   // Changes UI after the server responds (after the UI event happens and the data has been sent)

}