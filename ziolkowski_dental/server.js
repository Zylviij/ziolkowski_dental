function datedConsole(input) {
    var d = new Date()
    console.log('' + (d.getMonth()+1) + '/' + (d.getDate()) + '/' +(d.getFullYear()) +' ' + (d.getHours()) + ':' + (d.getMinutes()) + ':' + (d.getSeconds()) + '$ ' + input)
}

console.log('Initialization:')
console.log('\tRequires:')

var express = require('express')
var app = express()
console.log('\t\tExpress: required')

var fs = require("fs")
console.log('\t\tfs: required')

var path = require('path')
console.log('\t\tpath: required')

var bodyParser  = require('body-parser')
console.log('\t\tbodyParser: required')

var nodemailer = require('nodemailer')
console.log('\t\tnodemailer: required')

console.log('\tSettings')

app.set('view engine', 'jade')
console.log('\t\tengine: ~jade')

app.use(bodyParser.urlencoded({ extended: true }))
app.use(bodyParser.json())
console.log('\t\tbodyParser: used')

app.set('views', path.join(__dirname, 'views'))
console.log('\t\tviews: ./views')

app.use(express.static(__dirname + '/public'))
console.log('\t\texpress.static: used')

// create reusable transporter object using SMTP transport
var transporter = nodemailer.createTransport();
console.log('\t\tnodemailer: configured')

console.log('\tViews')

app.get('/', function(req, res){
    datedConsole('Request to \'/\'')
    datedConsole('\t Sending response')
    res.render('index')
    datedConsole('\t Response sent')
})
console.log('\t\t\'/\': defined')

app.get('/special', function(req, res){
    datedConsole('Request to \'/special\'')
    datedConsole('\t Sending response')
    res.render('special')
    datedConsole('\t Response sent')
})
console.log('\t\t\'/special\': defined')

app.get('/newpatient', function(req, res){
    datedConsole('Request to \'/newpatient\'')
    datedConsole('\t Sending response')
    res.render('newpatient')
    datedConsole('\t Response sent')
})
console.log('\t\t\'/newpatient\': defined')

app.get('/concern', function(req, res){
    datedConsole('Request to \'/concern\'')
    datedConsole('\t Sending response')
    res.render('concern')
    datedConsole('\t Response sent')
})
console.log('\t\t\'/concern\': defined')

app.post('/', function(req, res){
    console.log(req.body);
    // send mail with defined transport object
    transporter.sendMail({
        from: req.body.firstName + (req.body.lastName===undefined? "" : (' ' + req.body.lastName)) + ' <' + req.body.email + '>', // sender address
        to: 'team@ziolkowskidental.com', // list of receivers
        subject: 'MESSAGE FROM WEBSITE', // Subject line
        text: (req.body.type===undefined? "DISLIKE Patient" : ('Patient Type: ' + req.body.type)) + '\n' + (req.body.phone===undefined? "" : ('Phone number: ' + req.body.phone + '\n')) + 'Message: ' + req.body.message // plaintext body
    }, function(error, info){
        if(error){
            console.log(error);
        }else{
            console.log('Message sent: ' + info);
        }
    });

});

var server = app.listen(3000, function () {
    var host = server.address().address
    var port = server.address().port

  console.log('Listening at http://%s:%s', host, port)
})
