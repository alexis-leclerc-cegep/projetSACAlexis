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
  
let boisOptions = [];
let error = null;
const errorDiv = document.querySelector(".error");
let info = "";
const infoDiv = document.querySelector(".info");

function getBois() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        let responseParsed = JSON.parse(this.responseText)
        if (this.readyState == 4 && this.status == 200) {
            for(let i = 0; i < responseParsed.length; i++) {
                console.log(responseParsed[i].name);
                /*
                var x = document.getElementById("typeBois_ListBox_Select");
                var option = document.createElement("option");
                option.value = arrayOfStrings[i];
                option.text = arrayOfStrings[i+1];
                x.add(option);
                */
                } 

            //Refresh le contenu
            var siteHeader = document.getElementById('typeBois_ListBox_Select');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
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
   