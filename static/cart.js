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

            let entry = document.createElement("li");
            entry.setAttribute("data-seller", seller);
            entry.setAttribute("data-amount", amount);

            let text = document.createElement("span");
            text.innerText = "Verkäufer " + seller + " Betrag " + amount + "€ ";

            let deleteLink  = document.createElement("a");

            deleteLink.onclick=(event) => {
                let myElement = event.srcElement.closest("li");
                let mySeller = myElement.getAttribute("data-seller");
                let myAmount = myElement.getAttribute("data-amount");

                removeFromCart(mySeller, myAmount);
                myElement.remove();
            };

            deleteLink.innerHTML = "<strong>Entfernen</strong>";

            text.append(deleteLink);
            entry.appendChild(text);

            document.getElementById("cartlist").appendChild(entry);
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

    let list = document.getElementById("cartlist");

    while (list.hasChildNodes()) {
        list.removeChild(list.firstChild);
    }
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
    }
}