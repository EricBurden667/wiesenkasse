// warenkorb array declaration
if (typeof warenkorb === "undefined" || warenkorb === null) {
  warenkorb = []
}


function showCart() {
    //warenkorb = "{47: 1, 13: 7}";
    //wtable = document.getElementById("warenkorb").innerHTML;
    //document.write(wtable);
    var ausgabe = '';
    for (var i = 0; i < warenkorb.length; ++i) {
        ausgabe += '<li id="nr' + i + '">';
        ausgabe += warenkorb[i];
        ausgabe += '<input type="button" value="X" id="loeschen" onclick="delItem(' + i + ');" />';
        ausgabe += '</li>';
    }
    document.getElementById('liste').innerHTML = ausgabe;
    /*
    <p id="warenkorb"></p>
    <button type="submit" onclick="delCart()" background-color: red>Alles löschen</button>
    <button type="button" formaction="/data/add" formmethod="post">Fertig</button>
    */
}

function submitCart() {
    const httpRequest = new XMLHttpRequest();
    function handler() {
      // Process the server response here.
      true;
    }

    httpRequest.onreadystatechange = handler;
    httpRequest.setRequestHeader(
      "Content-Type",
      "application/json"
    );
    httpRequest.open("POST", "/data/add", true);
    httpRequest.send(warenkorb);
}

function addArticle() {
    // Get the values of the input fields
    // TODO: Try "valueAsNumber" instead of "value"
    const verkID = document.getElementById("verkID").value;
    const betrag = document.getElementById("betrag").value;
    
    console.log("DEBUG: Zuweisung: verkID=" + verkID + ", betrag=" + betrag);

    // Not a Number validation
    if (isNaN(parseInt(verkID)) || isNaN(parseFloat(betrag))) {
      // TODO: Use "postMessage" for feedback to user
      console.log("ERROR: Invalid Input");
    } else {
      //warenkorb += '{"verkID": verkID, "betrag": betrag}';
      console.log("DEBUG: Warenkorb Items: verkID: " + verkID + ", betrag: " + betrag);
      warenkorb.push("{verkID:" + verkID + ", betrag:" + betrag + "}");
    }
    console.log("DEBUG: Warenkorb: " + warenkorb);

    //document.getElementById("warenkorb").innerHTML = warenkorb;
    //return warenkorb;
    showCart();
}

function delCart() {
  true;
}

function delItem(id) {
  warenkorb.splice(id, 1);
  showCart();
}