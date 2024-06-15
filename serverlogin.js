const express = require('express');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(express.static(__dirname));

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/index.html');
});

app.post('/login', (req, res) => {
    const { email, password } = req.body;
    // Add your login logic here (check email and password)
    if (email === 'user@example.com' && password === 'password') {
        res.send('Login successful!');
    } else {
        res.status(401).send('Login failed. Invalid email or password.');
    }
});

app.listen(port, () => {
    console.log(`Server is listening at http://localhost:${port}`);
});
