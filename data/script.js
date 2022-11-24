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
        let woodArray
        if (this.readyState == 4 && this.status == 200) {
            for(let i = 0; i < responseParsed.length; i++) {
                let currentWood = responseParsed[i].name;
                let currentId = responseParsed[i].id;
                var x = document.getElementById("dropDown_TypeBois");
                var option = document.createElement("option");
                option.value = currentId;
                option.text = currentWood;
                x.add(option);
            } 

            //Refresh le contenu
            var siteHeader = document.getElementById('dropDown_TypeBois');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';
        }
    };
    xhttp.open("GET", "getWoodName", true);
    xhttp.send();
}

function getWoodDetails(selectedObject){
    id = selectedObject.options[selectedObject.selectedIndex].value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        console.log(this.responseText);
        const responseParsed = JSON.parse(this.responseText.slice(1, -1));
        console.table(responseParsed.type);
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("nomBois").text = ": " + selectedObject.options[selectedObject.selectedIndex].text;
            document.getElementById("typeBois").text = ": " + responseParsed.type;
            document.getElementById("origineBois").text = ": " + responseParsed.origine;
            document.getElementById("tempSechBois").text = ": " + responseParsed.drying + " secondes";
            document.getElementById("tempMinBois").text = ": " + responseParsed.temp + " °C";
        }
    }

    xhttp.open("GET", "getWoodDetails?id=" + id, true);
    xhttp.send();

}

/*
getBois().then(data => {
    let option;
    console.log(data);
    Object.entries(data).forEach(bois => {
    option = document.createElement("option");
    option.text = bois[1].name;
    boisSelect.add(option);
    });
});
   
*/