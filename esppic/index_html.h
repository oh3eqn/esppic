const char index_html[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">

    <title>ESPPIC - Upload file</title>
    <style>
        body {
            background-color: darkslategrey;
            font-family: sans-serif;
            color: #ffffff;
        }
        
        header img {
            vertical-align: top;
        }
        
        a {
            color: #8080ff;
        }
        
        .labu {
            display: inline-block;
            text-align: center;
        }
        
        .labu label {
            display: block;
            font-size: 60%;
        }
        
        .labu button {
            height: 40px;
        }
        
        .labu select {
            height: 40px;
        }
        
        .dropzone {
            position: relative;
            border: 2px dotted #ccc;
            width: 150px;
            height: 150px;
            margin: 0px 10px 10px 10px;
            padding: 25px 10px 10px 10px;
            float: left;
            border-radius: 20px;
        }
        
        .dropzone img {
            width: 100%;
            height: 100%;
        }
        
        .dropzone p {
            position: relative;
            text-align: center;
            margin: -178px 0 0 0;
            color: red;
            font-size: 18px;
        }
        
        #dropzone.hover {
            border: 2px dashed #0c0;
            filter: hue-rotate(180deg);
            -webkit-filter: hue-rotate(180deg);
        }
        
        .block label {
            display: inline-block;
            width: 80px;
            text-align: right;
        }
        
        .config {
            float: left;
            font-size: 10px;
            line-height: 90%;
        }
        
        .config h4 {
            margin: 0 0 10px 0;
            padding: 0;
            font-size: 120%;
        }
        
        .config label {
            font-family: monospace;
            color: white;
        }
        
        .config span {
            display: inline-block;
            width: 200px;
            margin-left: 3px;
            font-size: 85%;
            white-space: nowrap;
            overflow: hidden;
            text-overflow: ellipsis;
        }
    </style>

    <script>
        var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);

        connection.onopen = function() {
            connection.send('Connect ' + new Date());
        };

        connection.onerror = function(error) {
            console.log('WebSocket Error ', error);
        };

        // Update screen info fields on data send from server/esp
        connection.onmessage = function(e) {
            //console.log('Server: ', e.data);
            var myData = e.data.substr(1);
            switch (e.data[0]) {
                case 'f':
                    document.getElementById('v_filename').innerHTML = myData;
                    break;
                case 's':
                    document.getElementById('v_size').innerHTML = myData;
                    break;
                case 'p':
                    document.getElementById('v_status').innerHTML = myData;
                    break;
            };
        }
    </script>
</head>

<body>
    <header>
        <!-- https://varvy.com/tools/base64/up.php -->
        <img alt="Logo" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAMIAAAAoAQMAAACW8LeWAAAABlBMVEUAAAD/AAAb/40iAAAAAXRSTlMAQObYZgAAAcdJREFUOMvF0rFu1EAQBuDxGclIp2ShokDKRHmCdFDhvAGUdOQNaBBNAnaUIgVC4Q3yAGmuprnlDdKBBMhOBUWkWylI3ii2/8zs2ncnHgAsrceaT+Mdj5fon13Jboxe4uHuKj8pAEff6SHQl5iDClB6rpJB5NH88lLiJ1EP0FZTj/IYN05iDXSyKJfHQVjWXJY8aw1Wks9jtgqaoBmkctKFl1f8kdoWOO6rKCW74in73GWeXdoXPutSleSA2EGyuU1/cJ2209p4CgJp8NZlLrdZy3XWTp2p06UczEhbbQ3wxjiuCXaQtz7IS5GWpTqOp5H4pA3iRaSLvIzzbFASQ+XXBeP6N9eDyAdbyioXRmKwkM7GmoXulrcqltFbMxvlRiULY9yTGdiNtX0GkSD9krkYpdqSe4pyKY4HQbwvZVNlR5OLKHYU9iJ9kJK276+JmYkUYQalcYUMdykv2E7ey1bJuQi+rGRzxu4eVLruNJyOUYAzP9UvMWhYxULmDZlsj1MUWpNePwuno9RsWDhZAPG8FX/L1yg/+zPfvRpE34ijD7hSuX1X+fb1eo2FbkOTzx/39q/MYeL3ib5tUyJlz/v46x7Qf73uACNKgP0KdMykAAAAAElFTkSuQmCC'>
        <!-- http://www.flaticon.com/packs/audio-and-video-controls -->
        <span class="labu">
        <button onclick="connection.send('RH');">
        <img alt="Run" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAAB60lEQVRIx72WsUsjURCHvzfsgss2KRarw9LWQLInQUvbdBZWkkIQrKy9JlcoaQJ2CiKksbMQon+CTRIhZyFifZWk2Gax2DDvittI7tgkmyhOOQy/efMNM/MMU8wWi8v4fohIGdUSqmUARHqIPKDaI467pt9/naRhspxarbpmMPgBHAEu0y3BcY5toXAi7XYyM4Hd2Cii2gLWmM9+IVIz9/f9caf8I16pHKDaWUAcYA3Vjq1UDjIrSF/eyYGEmchEvo8qkRHzFMtHxQFcVFtarbrvCdKGZmKxOzvQbMLq6ly4TBQdARhbLC7jeb8nvr7RgM1NGA7h5gYuLiCO86F6e/sm+H6YC43jwPY2XF3B1lY+VL4fCiLluQgHAdTr0GxiV1amx4qUBdXSQq1cX8dcXsLeHiwtZceoluR9/Bcxz4NaDVotbKGQlaAsfIa57t8eZVFCpLew8HAI19ewu4sZDLJ60HPSrVidV9s+PmJOT+HlZVqTHxxU56sgiuDsDHN3NztWtecQx108L8k1C7e32PNzTBTlG7Q47kp6LE4mhj0/Y5+eYH8fGo284uA4x6bffzVjB6a74JrOvA02CEJpt5OvWdcAqeMQSD4kDofjV+1rT+aoEhsEIfAzZzUJjlO3QRD+Lz7xV/GZ35Y/k8LYjiJO2AsAAAAASUVORK5CYII='>
        </button>
        <label>Run</label>
        </span>

        <span class="labu">
        <button onclick="connection.send('RL');">
        <img alt="Halt" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAABnklEQVRIx72WwUrjUBSGv/vThuhasnBbxOUUTOcxXCmuArOelWsLwgj6HELATXc+RptCZim+QXCtwci9s8i1aW2njk7jDwdyTk7+m/uf3HNiWAOXJJErywFSjLUHQOxvZUhTrM1MGE5MmhZ/4zArifv9ruv1hkhnQJf1qJAuzd3dlcnz6t0F7PFxH7gGvvEx/AZ+aDTK54NaID85+QmMP0GOf2bsOZZ34N98/A+S8K5k8P11J3rV3MuyQG6CALO7W1sUNfEoauJB8HaBLnDtOekAuF5vuFKWoyM4PGyIz8/ri4uLJuf2Fm5uluRy+/tn5PkvuSSJ/NeyjO3tRX9rq7Z1OTPN7dAlSSRXloMN6L4KXVeWAyHFtAUplj+h7cDaA80d/zYQi5YhIGuRPxPStMUiT4W1WYtFzmTCcOL7x6ZRmTCcyKRpgbVXK1MeHxf9p6fa1uU08lyaNC3MbMDs7U3e9iMTBLCzUzsvL7iimDU7Op06/vCAe35emg3m/n5g8rz6mnYNoNEoRzr9z3pUSKfzU631kfn1Q3/Tvy1/APGlqcv0FVZ3AAAAAElFTkSuQmCC'>
        </button>
        <label>Halt</label>
        </span>

        <span class="labu">
        <button onclick="connection.send('RP');">
        <img alt="Reset" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAADFUlEQVRIx7WWPWhTURTHf/fyAg1vkfBsHEIREQeHGtrEUlJBxKEgXaqjikOR6qAFl6JLGrRKUSlRMjiIiIODFDEOIuIgtNImhbiVV8ggHWyRR6CE2CTc6/DS5jvRov/tnXvP5zvnf66gA3Qw2ItphpEyhFKDKBUCQMo0Uq6iVJp8PiUyma12NkQroRob84ifP+8AtwEPnVHCMO7pAwdmZTJZ6upARyJBlHoBnODv8A0pr4jFxUxbB3p4+Dow3xi1tizE0BAcPOgKNjZgeRm2t5uzgSnx9WuiyUEl8pVa47qvD3HzJgwNNcdbLsOHD+hnzxCOU+9EypO7mYiamqfqyjI6CrdugdfrfhcK6PV1N6rjx8EwXLnjoK9eRfz4UVcubVlhmUyWDIDKD60aP3UKpqddI9ks3L0Ltl1N1zTdrKamwOeDWAxu3IBfv3ZvnBC53G1gRuhgsBevd6Ou7q9fQyDg1jkabVVrF4cPw6NH4PfDmzcwP19fqkIhYGCaYZSqb8XHj9GBAOL9eygW2/fN6Ch6cxPh98OFC3DoEORy8OABgAfTDEukDDUprqwgFhY6Gwe04yD6+6uCkRHw1MQqZUii1CD7hHj7Fr22VhU4DvrJk5qJVYNyb/xrEYvBxER3D8UiYm7ObVmAp08RuVytg5DRpHT6NJw54yp9+QK23dmJbcOrV3D0KHz82JyljkTeodTYXvu9fOl2BaBtGzE52fVftIWUSYmUq3uCa9f2jAOIY8fQ4+PsG1KuSpRK1wmXlqpdYtuIXf5ph54e9OXLcPZsC1pWaYN8PoXXWwI8PHzoHkxOwsWLCMuCT5/at6nPB9EoYmAAvn9vvFsin0/JyrKYrdN8/hydTrs0EI/DuXNoy6qee70QCiESCdf4zk7jFINh3BOZzFZbstM+HyKRcCljF9ksulxGHDlSJbtCAe7fh8+fW5JdR7rGNOHSJTh/vsqqtXS9tISOxxuZtJmuuy0cenqgvx9dyUY4DqRSkM//+cL5XytTNk3e4mJGW1YYmKlE1A0lDCOqLSvcaLztq+JfPlt+A8haStNWB+5QAAAAAElFTkSuQmCC'>
        </button>
        <label>Reset</label>
        </span>

        <span class="labu">
        <button onclick="connection.send('DL');">
        <img alt="Download" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAACUUlEQVRIx72WP2hTURTGf/e9m4CYgi2SoCgutiL9gzYNIg42uGnFgos4BEexRXHqYBEN7ZCxIi4uTjq5tO5ODiENhTaB/qO0GdL2tbSgLr7cm+fQJD5q8l7bVL/pvXMP37nnO/fccwUemKMrIlExg3IU6HMQUQCBky1jZIFphcx0k9tsxCHqGfN0Bk3US2AEkHhDASmNTHaSt30DLHHxqsb8APRwOMya6EftLM+4jYb7Z4GOIY2ZPgI5QI/GTC/QMVQ3g8rO00CA5lAy0deqmQiX5hm/nbcOPwRg9+1HX7k0MtZJ3jYAKgX1JJfhNsITo4QnRpHhNl+5KpwYc3RFKqfluDEyR1fEkKjYAY7iUSD3egj6vLxO3OjlwuwkLYnBmi107xbnv30ieOWyZwSDclQs0DHlIAYaOZ2bfMfJO/11135MfaU4OETjLna+GNX2b4SNx6+wl9b+sttLa1hPXntm4CCihp+QqmhRiCewF1f/kC+uUognUEXLtxCGwMn6Oen1rb0g8yvY8ysU4gn0+pYvucDJyjJGVuDUaiCCAc5+fgNA8f5THLu0F2Rjm7XrDwAof/+Jn38F0xKYdlvMUy2Ebt+sfStrp7bmJj6QP0ZWKmQmQEnV64XI+zHU9q73YT/d2rB8CpmR3eQ257mUAl7s9wgN9DfTaKlucpsSQCOTJuou0KOsHaxnY8gz4UOxqXXLLc+sRib/zXUtJab61Vu9rmt90M7yjMB5DpSamQVClYbdU+3/jsxqJhoZA8YrA91XfmBcI2P7yRu+Ko7z2fIb92ru5VCD1jEAAAAASUVORK5CYII='>
        </button>
        <label>Download</label>
        </span>

        <span class="labu">
        <button onclick="connection.send('FL');">
        <img alt="Flash" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAYAAADgdz34AAACOklEQVRIx72WPUgjQRTHfzO7KUKIdik0iAS0vYMkh/jRBUGsBbWQFFaHoJVItEgTsbYTRKys7cSwhYUpTCJEwd4iWCTtRpDEnSt2zgRvs8nK3b1m37yd9995/3kfK/ARlcnEkDINpICkfgJUgXugiuNUhGU1+mEIT+C5uRDh8D5S5oAQ/tIGCrRah6JUag/8gFpc/A6cA98IJg9AVhSLtV6j7F04S0s/gfIXwNE+ZY3xZwT65OW+lExNoba2EKYJpgmdDmp3F9FqeVH243ck8oNzl5b+fK+uIqanIZGAiQk4OfECR2Oca0xNUTi870eLikZhZqZrODuDx0d/uiKRHIDQqVj3Pf3GBqytufrtLRQKw9xJG8eJS53nfcGVYcDysrt4fkYdHXXt4+OoSKSfawgp02ZP8XgXysICjIy4i3odkcvB5CRibAxVq8HBgZ97ytQV2l9WVrr6/HxXf3mBfB7x/u7nnZS+EcTjqE4Hbm7g4gJs27XbNuztId7eBt1DyvR9Xa8jtrddPZ2G9XVwHMjnodkcqvqkbly+ogwDNjdd/fgYnp6Gre6q1F3RXzIZt7guLxHX10Hax71vBCoaRRkGIpuFuzvU6WnQ/lQ1cZwKUra9akEkk24Wvb6iCoVBGeNVaBUpLKuB4xx6bmk2IZFA2TYiFgt6+oKwrIb4aHaRSOVzP1KjozA7i7i6IvBsaLXSolRqD9+ug1DzuV0DiGKxpgxjR2/4MrgyjJ3eqfbPR+b/H/p/+7flF9lK1P6OUddSAAAAAElFTkSuQmCC'>
        </button>
        <label>Flash</label>
        </span>

        <span class="labu">
        <select name="device ">
        <option value="16F1705 " selected>PIC16F1705</option>
        </select>
        <label>Select device</label>
        </span>

    </header>

    <div style="overflow:auto; margin-top:10px;">
        <div class="dropzone">
            <img id="dropzone" alt="Dropzone" src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAPoAAAD6AgMAAAD1grKuAAAACVBMVEUAAGf/AAD///8pCBZ1AAAAAXRSTlMAQObYZgAABNFJREFUaN7tm0GS5CgMRa2O0H4WpX0fhSOwgPvM0aezsgySEJYwkdGLsSMqo9LpZwPGXx+Bj2PYoLw+658/zOfXvs/f8HUY1HQcVM6vfV+ETz8f9KKoin2f56kdWzWfH/7hH/7hH/5z/N/W/59Y9fqvnB/Q9gW2cn5APj/6vmd7tk9uUC83D6/eVpxnx93S1uWvCxC4/GUBKMLnu23v3gOM8emCL4EbnC6qH+lfeX7ugMLND4IaEWicFhJqjT0g0zOHBHpaypX4aP8Q5PPiiYPF3OVrDSpU+V/yv13+uvv96x13zf869vivTb7c4JnaQV7mgQcMTPZx2DVZ8SAiDsnrNIy6JiteRqwq+YbVGY8i4GCRfPuJHSN4kPGC8iJPMl5xabD4ofwyYIPm6eQn7Yey+FiPSfsBa+JiGonh1r6+gOEl2FeQPAjJC/Q/ktXHVV7ZDanMPg/92pAGZfJ5lE5HKZbPK6OkIpbL65tTF3mUNkn7Cpcnefm348A4r1waff9AaY3nffH1Q28DjwfpUvH7C7uHhk5kvh918d+D5yr48xbR+JCRNLn1Jw3QTunpnyw+vPlq8qZ+yeK/TTGwczr6B0Px87tNSoxH0XngXRiY8aP+ob579ayU1X5j/CJ996pqFBG/xv4j+Rb/JH/R/3TnfVeG1crnpZAmcSKPB9F8XcX7aRd4WOeRNx/2KECtWXx+jCM5zBPnWRDt5XL5YhT/7MhLPCt+mOfNLzxA+yHMg/QAyzxKB2fyqPwHcKESKYPWMN1/GP6R8SBH/IKf6ifjUWYcLH7UL1CqwBw056f6hwafhZJd+0fFQ9ctwU/9o8qBYFcji0/D/VM89cceOA8z/VR8nfDT/keC56H8Ds9DeesZCzwP5Xd4bqTCfDarf4cXTuYGL53MOq9t7CKvjNwyr4zcMk9DKE+ufyQl32XCK/+YjP4DoxFMrv4xHuUTCqZ+GPpVdPQq4/Wn+seurzLGcKV/xvWV/E/4uf4p+TfrP/rHzqvqS/3EC/2rZvUlP+1/7SjQ+XIRf6Z8qyXqCYM4n7R3GeOnzw/p+jV+qH5/skL+Zaj+ov8Zqr/AF2G89Ugg7h/5oGnFf7IeI8Uwzca/xeRJW3kjfzSM35j/J23lI+Nfxg8jocj4F4TgjAM5b/wK3PBJ9S+h/F87kLT651D+jxtWGcrz2vh3GAfHx795cMJq/H0xfsWW9NMJxRh/HkoqiyHyBzHe9LFu/qg9wcWy8T5P53gvWzbe5/FMOCXLxofyX7r6dY0vKmkJUkjd/F1W04QkhdTNPyY1TSkTin7+U01mouzrofkT0kmUMjvOTrKzlDWpaXP2/KWL+QOVhEj2/MFk/gKGQfza/Md7rRCZyw4iPFWVxp/Nn0zmP6iMsxBHLP/XuyDaixYc/TvafA3Zaw4C/QfLOAe0NH+SxymsJT7J6h+LfJWTOGmRhzJOAC7Nv2TTAYZ5Eg42LfNf/MFN6/PfWT4Gqzykvfl33Jy//7rHN8n755LHz63f2Fs/srt+ZXf9zO76nd31Q0eNNADNa1k3109RbP1Wvqja1vqx3fVrRwgvl/dma/0e7BU/tAAwO3d35/J+Ez5LiJ/t2T67ba7f331/4Hn/7eEf/uEf/nn/7fh777+lu+9vL70//h+PmRTtxqDv+AAAAABJRU5ErkJggg=='>
            <p>Drop .hex here</p>
        </div>
        <div class="block">
            <label>Filename:</label>
            <span id="v_filename">...</span>
        </div>
        <div class="block">
            <label>Size:</label>
            <span id="v_size">...</span>
        </div>
        <div class="block">
            <label>Status:</label>
            <span id="v_status">...</span>
        </div>
    </div>

    <div id="config1" class="config">
        <h4 id="config1hex">CONFIG1 0x----</h4>
        <label id="config1bits">- - - - - - - - - - - - - -</label><br>
        <label>| | | | | | | | | | | | | |</label><br>
        <label>| | | | | | | | | | | | | +</label><label id="cfl1_0">––</label><span id="cfg1_0"></span><br>
        <label>| | | | | | | | | | | | +––</label><label id="cfl1_1">––</label><span id="cfg1_1"></span><br>
        <label>| | | | | | | | | | | +––––</label><label id="cfl1_2">––</label><span id="cfg1_2"></span><br>
        <label>| | | | | | | | | | +––––––</label><label id="cfl1_3">––</label><span id="cfg1_3"></span><br>
        <label>| | | | | | | | | +––––––––</label><label id="cfl1_4">––</label><span id="cfg1_4"></span><br>
        <label>| | | | | | | | +––––––––––</label><label id="cfl1_5">––</label><span id="cfg1_5"></span><br>
        <label>| | | | | | | +––––––––––––</label><label id="cfl1_6">––</label><span id="cfg1_6"></span><br>
        <label>| | | | | | +––––––––––––––</label><label id="cfl1_7">––</label><span id="cfg1_7"></span><br>
        <label>| | | | | +––––––––––––––––</label><label id="cfl1_8">––</label><span id="cfg1_8"></span><br>
        <label>| | | | +––––––––––––––––––</label><label id="cfl1_9">––</label><span id="cfg1_9"></span><br>
        <label>| | | +––––––––––––––––––––</label><label id="cfl1_10">––</label><span id="cfg1_10"></span><br>
        <label>| | +––––––––––––––––––––––</label><label id="cfl1_11">––</label><span id="cfg1_11"></span><br>
        <label>| +––––––––––––––––––––––––</label><label id="cfl1_12">––</label><span id="cfg1_12"></span><br>
        <label>+––––––––––––––––––––––––––</label><label id="cfl1_13">––</label><span id="cfg1_13"></span><br>
    </div>

    <div id="config2" class="config">
        <h4 id="config2hex">CONFIG2 0x----</h4>
        <label id="config2bits">- - - - - - - - - - - - - -</label><br>
        <label>| | | | | | | | | | | | | |</label><br>
        <label>| | | | | | | | | | | | | +</label><label id="cfl2_0">––</label><span id="cfg2_0"></span><br>
        <label>| | | | | | | | | | | | +––</label><label id="cfl2_1">––</label><span id="cfg2_1"></span><br>
        <label>| | | | | | | | | | | +––––</label><label id="cfl2_2">––</label><span id="cfg2_2"></span><br>
        <label>| | | | | | | | | | +––––––</label><label id="cfl2_3">––</label><span id="cfg2_3"></span><br>
        <label>| | | | | | | | | +––––––––</label><label id="cfl2_4">––</label><span id="cfg2_4"></span><br>
        <label>| | | | | | | | +––––––––––</label><label id="cfl2_5">––</label><span id="cfg2_5"></span><br>
        <label>| | | | | | | +––––––––––––</label><label id="cfl2_6">––</label><span id="cfg2_6"></span><br>
        <label>| | | | | | +––––––––––––––</label><label id="cfl2_7">––</label><span id="cfg2_7"></span><br>
        <label>| | | | | +––––––––––––––––</label><label id="cfl2_8">––</label><span id="cfg2_8"></span><br>
        <label>| | | | +––––––––––––––––––</label><label id="cfl2_9">––</label><span id="cfg2_9"></span><br>
        <label>| | | +––––––––––––––––––––</label><label id="cfl2_10">––</label><span id="cfg2_10"></span><br>
        <label>| | +––––––––––––––––––––––</label><label id="cfl2_11">––</label><span id="cfg2_11"></span><br>
        <label>| +––––––––––––––––––––––––</label><label id="cfl2_12">––</label><span id="cfg2_12"></span><br>
        <label>+––––––––––––––––––––––––––</label><label id="cfl2_13">––</label><span id="cfg2_13"></span><br>
    </div>
    <div style="clear:both;"></div>
    <br/>

    <a href="/readconfigs">Read config areas</a>
    <br/>
    <a href="/flash">Flash</a><br/>
</body>


<script>
    //----------- START OF DRAG AND DROP FROM http://html5demos.com/dnd-upload ---------

    var dropzone = document.getElementById('dropzone'),
        fileupload = document.getElementById('upload');

    function readfiles(files) {
        // debugger;
        var formData = new FormData();
        for (var i = 0; i < files.length; i++) {
            formData.append('file', files[i]);
        }

        // now post a new XHR request
        var xhr = new XMLHttpRequest();
        xhr.open('POST', '/upload');

        xhr.onload = function() {};

        xhr.upload.onprogress = function(event) {
            if (event.lengthComputable) {
                var complete = (event.loaded / event.total * 100 | 0);
                document.getElementById('v_progress').innerHTML = 'Uploading - ' + complete + '%';
            }
        }

        xhr.send(formData);
    }

    dropzone.ondragover = function() {
        this.className = 'hover';
        return false;
    };
    dropzone.ondragend = function() {
        this.className = '';
        return false;
    };
    dropzone.ondrop = function(e) {
        this.className = '';
        e.preventDefault();
        readfiles(e.dataTransfer.files);
    }

    //----------------------------------------------------------------------------------

    var configItems = {
        "1": {
            desc: "Always 1",
            values: {
                "1": "Unused",
                "0": "ERROR"
            }
        },

        "FCMEN": {
            desc: "Fail-Safe Clock Monitor Enable",
            values: {
                "1": "Fail-Safe Clock Monitor and internal/external switchover are both enabled.",
                "0": "Fail-Safe Clock Monitor is disabled"
            }
        },

        "IESO": {
            desc: "Internal External Switchover",
            values: {
                "1": "Internal/External Switchover mode is enabled",
                "0": "Internal/External Switchover mode is disabled"
            }
        },

        "/CLKOUTEN": {
            desc: "Clock Out Enable",
            values: {
                "1": "CLKOUT function is disabled. I/O function on the CLKOUT pin.",
                "0": "CLKOUT function is enabled on the CLKOUT pin"
            }
        },

        "BOREN": {
            desc: "Brown-out Reset Enable",
            values: {
                "11": "BOR enabled",
                "10": "BOR enabled during operation and disabled in Sleep",
                "01": "BOR controlled by SBOREN bit of the BORCON register",
                "00": "BOR disabled"
            }
        },

        "CP": {
            desc: "Code Protection",
            values: {
                "1": "Program memory code protection is disabled",
                "0": "Program memory code protection is enabled"
            }
        },

        "MCLRE": {
            desc: "MCLR/VPP Pin Function Select",
            values: {
                "1": "MCLR/VPP pin function is MCLR; Weak pull-up enabled",
                "0": "MCLR/VPP pin function is digital input; MCLR internally disabled; Weak pull-up under control ofWPUA3 bit"
            }
        },

        "PWRTE": {
            desc: "Power-up Timer Enable",
            values: {
                "1": "PWRT disabled",
                "0": "PWRT enabled"
            }
        },

        "WDTE": {
            desc: "Watchdog Timer Enable",
            values: {
                "11": "WDT enabled",
                "10": "WDT enabled while running and disabled in Sleep",
                "01": "WDT controlled by the SWDTEN bit in the WDTCON register",
                "00": "WDT disabled"
            }
        },

        "FOSC": {
            desc: "Oscillator Selection",
            values: {
                "111": "ECH: External Clock, High-Power mode (4-20 MHz): device clock supplied to CLKIN pin",
                "110": "ECM: External Clock, Medium-Power mode (0.5-4 MHz): device clock supplied to CLKIN pin",
                "101": "ECL: External Clock, Low-Power mode (0-0.5 MHz): device clock supplied to CLKIN pin",
                "100": "INTOSC oscillator: I/O function on CLKIN pin",
                "011": "EXTRC oscillator: External RC circuit connected to CLKIN pin",
                "010": "HS oscillator: High-speed crystal/resonator connected between OSC1 and OSC2 pins",
                "001": "XT oscillator: Crystal/resonator connected between OSC1 and OSC2 pins",
                "000": "LP oscillator: Low-power crystal connected between OSC1 and OSC2 pins"
            }
        },

        "LVP": {
            desc: "Low-Voltage Programming Enable",
            values: {
                "1": "Low-voltage programming enabled",
                "0": "High-voltage on MCLR must be used for programming"
            }
        },

        "/DEBUG": {
            desc: "In-Circuit Debugger Mode",
            values: {
                "1": "In-Circuit Debugger disabled, ICSPCLK and ICSPDAT are general purpose I/O pins",
                "0": "In-Circuit Debugger enabled, ICSPCLK and ICSPDAT are dedicated to the debugger"
            }
        },

        "/LPBOR": {
            desc: "Low-Power BOR Enable",
            values: {
                "1": "Low-Power Brown-out Reset is disabled",
                "0": "Low-Power Brown-out Reset is enabled"
            }
        },

        "BORV": {
            desc: "Brown-out Reset Voltage Selection",
            values: {
                "1": "Brown-out Reset voltage (V BOR ), low trip point selected",
                "0": "Brown-out Reset voltage (V BOR ), high trip point selected"
            }
        },

        "STVREN": {
            desc: "Stack Overflow/Underflow Reset Enable",
            values: {
                "1": "Stack Overflow or Underflow will cause a Reset",
                "0": "Stack Overflow or Underflow will not cause a Reset"
            }
        },

        "PLLEN": {
            desc: "PLL Enable",
            values: {
                "1": "4xPLL enabled",
                "0": "4xPLL disabled"
            }
        },

        "ZCDDIS": {
            desc: "ZCD Disable",
            values: {
                "1": "ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON",
                "0": "ZCD always enabled"
            }
        },

        "PPS1WAY": {
            desc: "PPSLOCK Bit One-Way Set Enable bit",
            values: {
                "1": "The PPSLOCK bit can only be set once after an unlocking sequence is executed; once PPSLOCK is set, all future changes to PPS registers are prevented ",
                "0": "The PPSLOCK bit can beset and cleared as needed(provided an unlocking sequence is executed)"
            }
        },

        "WRT": {
            desc: "Flash Memory Self-Write Protection",
            values: {
                "11": "Write protection off",
                "10": "0000h to 1FFh write protected, 0200h to 1FFFh may be modified by PMCON control",
                "01": "0000h to 0FFFh write protected, 1000h to 1FFFh may be modified by PMCON control",
                "00": "0000h to 1FFFh write protected, no addresses may be modified by PMCON control"
            }
        },
    }


    // no=config word number, bs=bit start, be=bit end, na=bit name 
    var configSpec = [
        { no: 1, bs: 13, be: 13, na: "FCMEN" },
        { no: 1, bs: 12, be: 12, na: "IESO" },
        { no: 1, bs: 11, be: 11, na: "/CLKOUTEN" },
        { no: 1, bs: 10, be: 9, na: "BOREN" },
        { no: 1, bs: 8, be: 8, na: "1" },
        { no: 1, bs: 7, be: 6, na: "CP" },
        { no: 1, bs: 6, be: 6, na: "MCLRE" },
        { no: 1, bs: 5, be: 5, na: "PWRTE" },
        { no: 1, bs: 4, be: 3, na: "WDTE" },
        { no: 1, bs: 2, be: 0, na: "FOSC" },
        { no: 2, bs: 13, be: 13, na: "LVP" },
        { no: 2, bs: 12, be: 12, na: "/DEBUG" },
        { no: 2, bs: 11, be: 11, na: "/LPBOR" },
        { no: 2, bs: 10, be: 10, na: "BORV"  },
        { no: 2, bs: 9, be: 9, na: "STVREN" },
        { no: 2, bs: 8, be: 8, na: "PLLEN" },
        { no: 2, bs: 7, be: 7, na: "ZCDDIS" },
        { no: 2, bs: 6, be: 6, na: "1" },
        { no: 2, bs: 5, be: 5, na: "1" },
        { no: 2, bs: 4, be: 4, na: "1" },
        { no: 2, bs: 3, be: 3, na: "1" },
        { no: 2, bs: 2, be: 2, na: "PPS1WAY" },
        { no: 2, bs: 1, be: 0, na: "WRT" },
    ];  


    var config = [0xC9C4, 0xfFff];
    UpdateConfigArea(config);

    function ToBinary14(data) {
        var tmp = "";
        tmp += (data & 0x2000 ? '1' : '0');
        tmp += (data & 0x1000 ? '1' : '0');
        tmp += (data & 0x800 ? '1' : '0');
        tmp += (data & 0x400 ? '1' : '0');
        tmp += (data & 0x200 ? '1' : '0');
        tmp += (data & 0x100 ? '1' : '0');
        tmp += (data & 0x80 ? '1' : '0');
        tmp += (data & 0x40 ? '1' : '0');
        tmp += (data & 0x20 ? '1' : '0');
        tmp += (data & 0x10 ? '1' : '0');
        tmp += (data & 0x8 ? '1' : '0');
        tmp += (data & 0x4 ? '1' : '0');
        tmp += (data & 0x2 ? '1' : '0');
        tmp += (data & 0x1 ? '1' : '0');
        return tmp;
    }

    function ToHex4(i) {
        return (i+0x10000).toString(16).substr(-4).toUpperCase();
    }

    function UpdateConfigArea(confs) {
        var myconf = [ToBinary14(confs[0]), ToBinary14(confs[1])];
        // Update headings
        for (var i=1; i<3; i++) {
            var e=document.getElementById('config'+i+'hex');
            e.innerHTML=e.innerHTML.substr(0,e.innerHTML.length-4)+ToHex4(confs[i-1]);
            var s="";
            for (var j=0; j<14; j++) {
                s+=myconf[i-1].charAt(j)+' ';
            }
            document.getElementById('config'+i+'bits').innerHTML = s;
        }
        // Update rows
        for (var i = 0; i < configSpec.length; i++) {
            var a = configSpec[i];
            for (var j = a.be; j <= a.bs; j++) {
                if (j == a.be) {
                    var myval = "";
                    for (var k = a.bs; k >= a.be; k--) {
                        myval += myconf[a.no - 1].charAt(13 - k);
                    }
                    document.getElementById('cfg' + a.no + '_' + j).innerHTML = "(" + myval + ") " + a.na + ' : ' + configItems[a.na].values[myval];
                    document.getElementById('cfg' + a.no + '_' + j).title = a.na + ' - ' + configItems[a.na].desc + '\x0A' + configItems[a.na].values[myval];
                    document.getElementById('cfl' + a.no + '_' + j).innerHTML = '––'
                } else {
                    document.getElementById('cfg' + a.no + '_' + j).innerHTML = '';
                    document.getElementById('cfl' + a.no + '_' + j).innerHTML = '&nbsp&nbsp;'
                }
            }
        }
    }
</script>

</html>
)=====";
