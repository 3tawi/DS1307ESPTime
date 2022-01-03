const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
    <head>
        <title>Great Projects</title>
        <script>
          var tz_val;
      function DisplayCurrentTime() {
          var dt = new Date();
  var weekday = new Array(7);
  weekday[0] = "Sunday";
  weekday[1] = "Monday";
  weekday[2] = "Tuesday";
  weekday[3] = "Wednesday";
  weekday[4] = "Thursday";
  weekday[5] = "Friday";
  weekday[6] = "Saturday";
  var dow = weekday[dt.getDay()];
  var da = dt.toLocaleDateString();
  var ti = dt.toLocaleTimeString(true);
  document.getElementById("datetime").innerHTML = (dow + " " + da + " " + ti);
        setTimeout('DisplayCurrentTime()', 1000);
      }
function myFunction() {
  var d = new Date();
  var n = d.getTime()/1000;
  var request = new XMLHttpRequest();
  var strLine = "localdatime?locadt=" + n;
  request.open("GET", strLine, false);
  request.send(null);
}
function myFunctionT() {
  var request = new XMLHttpRequest();
  var nt = document.getElementById("mytmie");
  var nd = document.getElementById("myddate");
  var strLine = "restime?htmie=" + nt.value;
      strLine += "&ddate=" + nd.value;
  request.open("GET", strLine, false);
  request.send(null);
}
function myFunctionTz() {
  var nz = document.getElementById("mylocatz");
  var request = new XMLHttpRequest();
  var strLine = "mytimezon?locatz=" + nz.value;
  request.open("GET", strLine, false);
  request.send(null);
}
function myFunctionS() {
  var request = new XMLHttpRequest();
  request.open("GET", "ntptime", false);
  request.send(null);
}
        function GetArduinoInputs()
        {
          var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
            tz_val = this.responseXML.getElementsByTagName('analog')[0].childNodes[0].nodeValue;
    }
    if(tz_val<0) { document.getElementById("TZmesg").innerHTML = "GMT" + tz_val; }
    else { document.getElementById("TZmesg").innerHTML = "GMT+" + tz_val; }
  }
  xhttp.open("GET", "readtemhu", true);
  xhttp.send();
            setTimeout('GetArduinoInputs()', 5000);
        }
      document.addEventListener('DOMContentLoaded', function() {
        DisplayCurrentTime(),GetArduinoInputs();
      }, false);
    </script>
      <style>
body {font-family: Arial, Helvetica, sans-serif;}

.container {
  padding: 16px;
}


/* Set a style for all buttons */
button {
  background-color: #4CAF50;
  color: white;
  padding: 14px 20px;
  margin: 8px 0;
  border: none;
  cursor: pointer;
  width: 100%;
}

button:hover {
  opacity: 0.8;
}


.slider {
  -webkit-appearance: none;
  width: 100%;
  height: 15px;
  background: #ffff00;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.slider:hover {
  opacity: 1;
}


.slider::-moz-range-thumb {
  width: 15px;
  height: 25px;
  background: #FF0F50;
  cursor: pointer;
}
  .data-input {
  text-align: center;
  background-color: #bbbbff;
  font-size:26px;
  color:red;
  border: 5px solid #444444;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  .button-blue {
  padding: 5px 5px 5px 5px;
  width: 100%;
  border: #fbfb00 solid 3px;
  background-color: #4444ff;
  color:white;
  font-size:20px;
  padding-bottom:5px;
  font-weight:700;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  .button-blue:hover {
  text-shadow: 2px 2px #ff0000;
  background-color: #2222aa;
  color: #ff93bd;
  }
  .text {
  background-color: #ff0000;
  font-size:76px;
  color: #ffff99;
  }
      marquee{
  width: 100%;
      font-size: 30px;
  font-weight:700;
      color: #ff0000;
      font-family: sans-serif;
      }
  table {
  text-align: center;
  width:100%;
  color: #0000ff;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  h1 {
  color: #ff0000;
  background-color: #ffff00;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
  div {
  border: 2px solid #ff0000;
  background-color: #bbbbff;
  color: #ff0000;
  -moz-border-radius: 7px;
  -webkit-border-radius: 7px;
  }
.contacts{
  text-shadow: 2px 2px #ffff00;
  text-align: center;
  font-style: blod;
  padding-top: 0px;
}
.DataCard{
  text-shadow: 2px 2px #000000;
  text-align: center;
  font-style: blod;
  overflow: auto;
  padding-top: 0px;
}
  </style>
    </head>
    <body>
   <tr>
  <div class="data-input">
    <div class="slidecontainer">
    <table>
   <td style="width:12%">
    <b class="button-blue" style="width:96%"><span id="TZmesg"></span></b></td>
   <td style="width:36%">
    <div class="slidecontainer" style="color:#00ffff;background-color:#000000">
    <b class="contacts" style= "font-size:36px"><span id="datetime"></span></b>
  </div></td>
   <td style="width:12%">
  <form action="/" method="POST">
    <div class="slidecontainer">
   <button onclick="myFunctionS()" class="button-blue" style="width:96%">NTP Time</button>
   </div>
  </form></td>
  </table>
  </div></div>
  </tr>
   <tr>
  <div class="data-input">
    <div class="slidecontainer">
    <table>
  <form action="/" method="POST">
   <td style="width:14%">
    <div class="slidecontainer">
   <input type="number" value="0" name="locatz" id="mylocatz" min="-12" max="+12" class="button-blue" style="width:32%">
   <button onclick="myFunctionTz()" class="button-blue" style="width:44%">Set</button>
   </div></td>
  </form>
  <form action="/" method="POST">
   <td style="width:36%">
    <div class="slidecontainer">
  <input type="date" value="0" name="ddate" id="myddate" class="button-blue" style="width:32%">
   <input type="time" value="00:00:00" name="htmie" id="mytmie" class="button-blue" step="2" style="width:32%">
   <button onclick="myFunctionT()" class="button-blue" style="width:22%">Set</button>
  </div></td>
  </form>
  <form action="/" method="POST">
   <td style="width:20%">
    <div class="slidecontainer">
   <button onclick="myFunction()" class="button-blue">Set local Time</button>
  </div></td>
  </form>
  </table>
  </div></div>
  </tr>
   <tr>
   <div class="data-input">
   <div class="slidecontainer">
  <form action="/restesp" method="POST">
  <input type="submit" name = "rerset" value="Restart ESP32" class="button-blue">
  </form>
  </div></div>
  </tr>
    </body>
</html>
)=====";
