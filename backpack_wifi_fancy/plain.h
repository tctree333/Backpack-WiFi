const char PLAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>

<head>
    <title>Backpack Console</title>
    <style>
        body {
            /* General Styles */
            font-size: 1.75em;
            text-align: center;
            font-family: Arial, Helvetica, sans-serif;
            color: white;
            background-color: royalblue;
        }

        #timer {
            /* Make timer BIG */
            font-size: 5em;
        }

        /* Different button colors depending on class */
        .blueButton {
            background-color: #6585e7;
        }

        .blueButton:hover {
            background-color: #2251dd;
        }

        .blueButton:active {
            background-color: #2251dd;
        }

        .greenButton {
            background-color: #4CAF50;
        }

        .greenButton:hover {
            background-color: #3e8e41;
        }

        .greenButton:active {
            background-color: #3e8e41;
        }

        .redButton {
            background-color: #d62929;
        }

        .redButton:hover {
            background-color: #ab2121;
        }

        .redButton:active {
            background-color: #ab2121;
        }

        /* General button styles */
        .button {
            display: inline-block;
            padding: 20px 30px;
            font-size: 1.5em;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            outline: none;
            color: #fff;
            border: none;
            border-radius: 15px;
            box-shadow: 0 9px #999;
        }

        .button:active {
            box-shadow: 0 5px #666;
            transform: translateY(4px);
        }
    </style>
</head>

<body>
    <h1 id="title">Backpack Console</h1>

    <p><span>Degrees: </span><span id="deg">no data</span></p>

    <p><span>Sensitivity:</span> <!-- adjust sensitivity -->
        <span><input min="5" max="350" value="30" type="number" id="sensitivity"></span>
        <span><button onclick="changeDifficulty()">Submit</button></span></p>


    <h1 id="timer">0</h1> <!-- timer display -->
    <!-- timer controls -->
    <button class="button blueButton" id="start" onclick="start()">Start</button>
    <button class="button blueButton" id="stop" onclick="stop()">Stop</button>
    <button class="button blueButton" id="clear" onclick="clearDisplay()">Clear</button>

    <script>
        // Setup variables
        var timer;
        var tStart;
        var degStart;
        var degrees;
        var sensitivity = 30;

        setInterval(function () { // update data every 100 ms
            document.getElementById("deg").innerHTML = getDeg();
        }, 100);

        document.body.onkeydown = function keyPress(event) { // triggers if key presssed
            if (event.key == "s") { // check if it's the s key
                document.getElementById("stop").click(); // click the stop button

            } else if (event.key == "c") { // check if it's the c key
                document.getElementById("clear").click(); // click the clear button

            } else if (event.key == "g") { // check if it's the g key
                document.getElementById("start").click(); // click the start button
            }
        }

        function buzz() { // trigger the buzzer
            getData("buzz");
        }

        function getDeg() { // return data from sensor
            getData("getData");
            return degrees;
        }

        function getData(url) { // get data from url
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200 && this.responseText != "ok") {
                    degrees = this.responseText;
                }
            };
            xhttp.open("GET", url, true);
            xhttp.send();
        }

        function start() { // activate timer
            buzz(); // trigger the buzzer
            changeColor("blueButton", "royalblue"); // change colors to blue
            clearInterval(timer); // stop timer
            document.getElementById("timer").innerHTML = 0; // clear display
            tStart = Date.now(); // set start time 
            degStart = getDeg(); // set current degrees (baseline comparison)
            timer = setInterval(function () { // actual timer loop
                // displays timer
                document.getElementById("timer").innerHTML = ((Date.now() - tStart) / 1000).toFixed(3);
                if (Math.abs(degStart - getDeg()) >= sensitivity && getDeg() != 0) {
                    // if difference is larger than set sensitivity
                    clearInterval(timer); // auto stop timer
                    changeColor("redButton", "firebrick"); // change colors to red
                    buzz(); // trigger the buzzer
                }
            }, 15); // update every 15 ms
        }

        function stop() { // manually stop timer
            clearInterval(timer); // clear the timer
            changeColor("greenButton", "forestgreen"); // change colors to green
            buzz();
            buzz();
            buzz(); // buzz 3 times
        }

        function clearDisplay() { // clear display
            tStart = Date.now(); // reset start time
            document.getElementById("timer").innerHTML = 0; // clear display
            changeColor("blueButton", "royalblue"); // change colors to blue
        }

        function changeColor(button, background) { // function to change colors
            var textElements = document.getElementsByClassName("button"); // get all buttons
            for (var i = 0; i < textElements.length; i++) { // loop through all buttons
                // clear the current color
                textElements[i].classList.remove("blueButton", "redButton", "greenButton");
                textElements[i].classList.add(button); // add color you want
                // change background color
                document.body.style.backgroundColor = background;
            }
        }

        function changeDifficulty() { // change difficulty (sensitivity)
            // get the value
            var value = Number(document.getElementById("sensitivity").value);
            if (value < 350 && value > 5) { // do a quick validation check
                sensitivity = value; // set the value
            }
        }
    </script>
</body>

</html>

)=====";