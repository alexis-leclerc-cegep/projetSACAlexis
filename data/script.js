function getNomFour () {
    console.log("Oui");
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("nom").innerHTML = this.responseText;
            //document.getElementById("color").style.backgroundColor = "red";
        }
    };
    xhttp.open("GET", "getNom", true);
    xhttp.send();
}

setInterval(function getTemperature(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if(this.status == 200) {
        document.getElementById("temp").innerHTML = this.responseText;
        }
    };
    xhttp.open("GET", "lireTemp", true);
    xhttp.send();
   }, 5000);

// function doAction(actionToDo) {
//     var params = String("actionToDo") + String("=") + String(actionToDo);
//     var xhttp = new XMLHttpRequest();
//     xhttp.open("POST", "ActionToDo", true);
//     xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
//     xhttp.send(params);
// }
  
const title = document.querySelector(".title");
const boisSelect = document.getElementById("bois");
const BASE_URL = "http://51.79.84.135:9999/api";
let boisOptions = [];
let error = null;
const errorDiv = document.querySelector(".error");
let info = "";
const infoDiv = document.querySelector(".info");

function getBois() {
    return new Promise((resolve, reject) => {
    fetch(`${BASE_URL}/woodlist`)
        .then(data => data.json())
        .then(woodlist => {
        resolve(woodlist);
        })
        .catch(err => {
        reject(err);
        });
    });
}

getBois().then(data => {
    let option;
    console.log(data);
    Object.entries(data).forEach(bois => {
    option = document.createElement("option");
    option.text = bois[1].name;
    boisSelect.add(option);
    });
});
   