var express = require('express')
var app = express()
console.log('express: required')

var http = require('http');
var https = require('https')

var fs = require("fs");
console.log('fs: required')


var options = {
    key: fs.readFileSync('./key.pem'),
    cert: fs.readFileSync('./cert.pem')
}

var path = require('path')
console.log('path: required')

var bodyParser  = require('body-parser');
app.use(bodyParser.urlencoded({ extended: true }));

app.use(bodyParser.json());
console.log('bodyParser: used')

app.set('views', path.join(__dirname, 'views'))
console.log('views: ./views')

app.use(express.static(__dirname + '/public'))
console.log('express.static: used')

app.set('view engine', 'jade');
console.log('view engine: jade')

var nodemailer = require('nodemailer');

// create reusable transporter object using SMTP transport
var transporter = nodemailer.createTransport();

app.get('/', function(req, res) {
    res.render('home');
});
console.log('/: defined')

app.get('/todo', function(req, res) {
    res.render('todo');
});
console.log('/todo: defined')

app.get('/index', function(req, res) {
    res.render('index');
});
console.log('/index: defined')

app.get('/special', function(req, res) {
    res.render('special')
})
console.log('/special: defined')

app.post('/', function(req, res){
    console.log(req.body);
    // send mail with defined transport object
    transporter.sendMail({
        from: req.body.firstName + ' ' + req.body.lastName + ' <' + req.body.email + '>', // sender address
        to: 'team@ziolkowskidental.com', // list of receivers
        subject: 'MESSAGE FROM WEBSITE', // Subject line
        text: 'Patient Type: ' + req.body.type + '\n' + 'Phone number: ' + req.body.phone + '\n' + 'Message: ' + req.body.message // plaintext body
    }, function(error, info){
        if(error){
            console.log(error);
        }else{
            console.log('Message sent: ' + info);
        }
    });

});

var port = 3000
var portssl = 3001
http.createServer(app).listen(port)
console.log('http')
https.createServer(options, app).listen(portssl)
console.log('https')
