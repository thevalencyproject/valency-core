/* This file is a part of The Valency Project which is released under the GNU Lesser General Public License v2.1
   Go to https://github.com/thevalencyproject/valency-core/blob/main/LICENSE for further license details.        */

const ws = new WebSocket("localhost:3030");     // Create the connection to the C++ Server


ws.onmessage = (event) => {             // Whenever a message arrives from the C++ Server
    let i = event.data.slice(0, 3);     // Get the function index (sent by C++ server as first 3 digits), and run it's respective function
    
    // ADD CUSTOM CASES FOR EVERY KIND OF SERVER MESSAGE YOU WILL RECEIVE HERE (if the server returns somthing for that task):
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

// EACH TASK MUST CONTAIN A SEND FUNCTION (i.e sending data to the C++ server)
//    -> CREATE A RECEIVE FUNCTION IF THE SERVER RETURNS SOMETHING AFTER IT RECEIVES THE SENT MESSAGE
function sendChangeColorButtonPressed(input) {      // Sends data to the server after UI event happens (i.e a logon button is clicked and the data is sent to the server)
    let i = "000";
    var serverMessage;

    ws.send(i + input);
}
function receiveChangeColorButtonPressed(input) {   // Changes UI after the server responds (i.e the server returns logon success or failure after it checks the previously sent message with its database)

}