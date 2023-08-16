/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

const ws = new WebSocket("localhost:3030");     // Create the connection to the C++ Server


// C++ Receiver Function
ws.onmessage = (event) => {                               // Whenever a message arrives from the C++ Server
    let index = event.data.slice(0, 3);                   // Get the function index (sent by C++ server as first 3 digits), and run it's respective function
    let data = event.data.slice(3, event.data.length);    // Cut the first 3 characters in the string

    // ADD CUSTOM CASES FOR EVERY KIND OF SERVER MESSAGE YOU WILL RECEIVE HERE (if the server returns somthing for that task):
    switch(i) {
    case "000": receiveLoginSuccess(data); break;
    case "001": receiveCalculatorResult(data); break;
    default: console.log("Invalid Server Message")
    }
};

// Login Task Functions
function sendLoginRequest() {   // C++ Sender Function
    let i = "000";
    var loginDetails = document.getElementById("user").value + document.getElementById("pass").value;

    ws.send(i + loginDetails);
}
function receiveLoginSuccess(input) {
    switch(result) {    // 1 = Success, 0 = Failure
    case 0: document.getElementById("successful").innerHTML = "LOGIN SUCCESS"; break;
    case 1: document.getElementById("successful").innerHTML = "LOGIN FAILURE"; break;
    default: console.log("Invalid Login Server Message");
    }
}

// Calculator Task Functions
function sendCalculatorRequest() {  // C++ Sender Function
    let i = "001";
    var calculatorDetails = document.getElementById("firstnum").value + " " + document.getElementById("secondnum").value;

    ws.send(i + calculatorDetails);
}
function receiveCalculatorResult(input) {
    document.getElementById("result").innerHTML = input;
}