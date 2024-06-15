document.addEventListener("DOMContentLoaded", function () {
    const registerForm = document.getElementById("registerForm");
    const registerSubmit = document.getElementById("registerSubmit");

    registerSubmit.addEventListener("click", function (event) {
        event.preventDefault();
        const name = document.getElementById("name").value;
        const phone = document.getElementById("phone").value;
        const email = document.getElementById("regEmail").value;
        const password = document.getElementById("regPassword").value;

        const userData = { name, phone, email, password };

        fetch('/register', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify(userData),
        })
        .then(response => response.text())
        .then(message => {
            alert(message);
        })
        .catch(error => console.error('Error:', error));