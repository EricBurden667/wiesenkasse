function showCart() {
    //warenkorb = "{47: 1, 13: 7}";
    wtable = document.getElementById("warenkorb").innerHTML;
    document.write(wtable);
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
    let verkID = document.getElementById("verkID").value;
    let betrag = document.getElementById("betrag").value;
    
    // Not a Number validation
    let text;
    if (isNaN(parseInt(verkID)) || isNaN(parseFloat(betrag))) {
      postMessage("Input not valid");
    } else {
      warenkorb += '{"verkID": verkID, "betrag": betrag}';
    }
    document.getElementById("warenkorb").innerHTML = warenkorb;
}

function delCart() {
    true;
}