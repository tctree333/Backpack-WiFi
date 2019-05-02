const char MAIN_page[] PROGMEM = R"=====(
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
            animation: color-change 30s linear infinite alternate both;
            position: absolute;
            margin-left: auto;
            margin-right: auto;
            left: 0;
            right: 0;
        }

        #timer {
            /* Make timer BIG */
            font-size: 5em;
        }



        /* CSS functionality of the change in button colors due to timer status changes */
        .startButton {
            background-color: #ffffff;
        }


        .stopBackdropGood {
            animation: stop-good 2s ease;
            background-color: #6fcf9a;
        }

        .stopBackdropBad {
            animation: stop-bad 2s ease;
            background-color: #cf6f8f;
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
            color: #77777755;
            border: none;
            border-radius: 10px;
            box-shadow: 3px 4px #bbb;
        }

        .button:hover {
            animation: pulsate 1s ease-in-out infinite both;
        }

        .button:active {
            animation: blink 0.5s both;
        }

        button.submit {
            font-size: 0.5em;
            padding: 15px 23px;
            border-radius: 3px;
            display: inline-block;
            cursor: pointer;
            text-align: center;
            text-decoration: none;
            background-color: #ffffffbb;
            outline: none;
            color: #555;
            border: none;
            box-shadow: 0 2px #999;

        }

        input {
            border: 2px dashed #fff;
            padding: 1em;
            height: 1.5em;
            width: 3em;
            color: #fff;
            border-radius: 2px;
            background-color: transparent;

        }

        @keyframes color-change {
            0% {
                background: #19dcea;
            }

            25% {
                background: #b22cff;
            }

            50% {
                background: #ea22e0;
            }

            75% {
                background: #bdd149;
            }

            100% {
                background: #0dd894;
            }
        }

        @keyframes stop-good {
            0% {
                background: #ffffff;
            }

            100% {
                background: #6fcf9a;
            }
        }

        @keyframes stop-bad {
            0% {
                background: #ffffff;
            }

            100% {
                background: #cf6f8f;
            }
        }

        @keyframes blink {
            0% {
                opacity: 1;
            }

            50% {
                opacity: 0.2;
            }

            100% {
                opacity: 1;
            }
        }

        @keyframes pulsate {
            0% {
                transform: scale(1);
            }

            50% {
                transform: scale(0.9);
            }

            100% {
                transform: scale(1);
            }
        }
    </style>
</head>

<body>
    <h1 id="title"> Backpack Console </h1>



    <p><span>Degrees: </span><span id="deg">no data... yet!</span></p>



    <p><span>Sensitivity:</span> <!-- adjusts sensitivity -->
        <span><input min="5" max="350" value="30" type="number" id="sensitivity"></span>
        <span><button class="button submit" onclick="changeDifficulty()">Submit</button></span></p>




    <h1 id="timer">0</h1> <!-- timer display -->
    <!-- timer controls -->
    <button class="button blueButton" id="start" onclick="start()">Start</button>
    <button class="button blueButton" id="stop" onclick="stop()">Stop</button>
    <button class="button blueButton" id="clear" onclick="clearDisplay()">Clear</button>

    <script>
        // Setups all the variables
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
            document.body.classList.remove("stopBackdropGood");
            document.body.classList.remove("stopBackdropBad");
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
                    document.body.classList.add("stopBackdropBad");
                    buzz(); // trigger the buzzer
                }
            }, 15); // update every 15 ms
        }

        function stop() { // manually stop timer
            clearInterval(timer); // clear the timer
            document.body.classList.add("stopBackdropGood");
            buzz();
            buzz();
            buzz(); // buzz 3 times
        }

        function clearDisplay() { // clear display
            tStart = Date.now(); // reset start time
            document.getElementById("timer").innerHTML = 0; // clear display
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