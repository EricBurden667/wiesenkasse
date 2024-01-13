var cart = [];

document.addEventListener("DOMContentLoaded", () => {
    document.getElementById("continue").addEventListener("click", (e) => {
        let seller = parseInt(document.getElementById("seller").value);
        let amount = parseFloat(document.getElementById("amount").value);

        if (seller > 0 && amount > 0) {
            let item = {
                "verkID": seller,
                "price": amount
            };

            cart.push(item);
            document.getElementById("seller").value = "";
            document.getElementById("amount").value = "";

            let table = document.getElementById("cartTableBody");           
            let row = table.insertRow();
            row.setAttribute("data-seller", seller);
            row.setAttribute("data-amount", amount);

            let sellerCell = row.insertCell(0);
            sellerCell.innerHTML = item.verkID;
            
            let amountCell = row.insertCell(1);
            amountCell.innerHTML = item.price;

            let deleteLink = row.insertCell(2);
            deleteLink.innerHTML  = document.createElement("a");

            deleteLink.onclick=(event) => {
                let myElement = event.srcElement.closest("tr");
                let mySeller = myElement.getAttribute("data-seller");
                let myAmount = myElement.getAttribute("data-amount");

                removeFromCart(mySeller, myAmount);
                myElement.remove();
            };

            deleteLink.innerHTML = "<strong>Entfernen</strong>";

            calculateTotalAmount();
        }

        e.preventDefault();
    });

    document.getElementById("deleteAll").addEventListener("click", (e) => {
        clearCart();
        e.preventDefault();
    });

    document.getElementById("submitAll").addEventListener("click", (e) => {

        let body = {"items": cart};

        try {
            let config = {
                "method": "POST",
                "headers": {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(body)
            };

            (async () => {
                let response = await fetch("/data/add", config);
                alert("Daten wurden übermittelt.");
                clearCart();
            })();
        } catch (error) {
            alert("Es ist ein Fehler aufgetreten!");
        }

        e.preventDefault();
    });
});

function clearCart() {
    cart = [];

    let tableBody = document.getElementById("cartTableBody");

    while (tableBody.hasChildNodes()) {
        tableBody.removeChild(tableBody.firstChild);
    }

    calculateTotalAmount();
}

function removeFromCart(seller, amount) {
    index = -1;

    for (i = 0; i < cart.length; i++) {
        if (cart[i].verkID === parseInt(seller) &&
                cart[i].price === parseFloat(amount)) {

            index  = i;
            break;
        }
    }

    if (index >= 0) {
        cart.splice(index, 1);
        calculateTotalAmount();
    }
}

function calculateTotalAmount() {
    let i = 0;
    let sum = 0;

    while (i < cart.length) {
        sum += cart[i].price;
        i++;
    }

    document.getElementById("totalAmount").value = sum;
}