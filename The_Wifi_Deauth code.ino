from flask import Flask, request

app = Flask(__name__)

# Store last received data
last_received_data = ""

# HTML Page
html_page = """
<!DOCTYPE html>
<html>
<head>
    <title>Python Deauth Simulator</title>
    <style>
        body {
            background-color: #111;
            color: #0f0;
            font-family: monospace;
            text-align: center;
            padding-top: 50px;
        }

        button, input[type="submit"] {
            background-color: #0f0;
            color: #111;
            padding: 12px 24px;
            font-size: 18px;
            border: none;
            cursor: pointer;
            margin-top: 10px;
        }

        input[type="text"] {
            font-size: 18px;
            padding: 6px;
            width: 300px;
        }

        #status {
            margin-top: 20px;
            font-size: 20px;
        }
    </style>
</head>
<body>

    <h1>🚨 Deauth Attack Simulator</h1>

    <button onclick="startDeauth()">Start Deauth Simulation</button>

    <div id="status"></div>

    <h2>Send Data to Python Server</h2>

    <form action="/submit" method="POST">
        <input name="userdata" type="text"
               placeholder="Enter data here" required />
        <input type="submit" value="Send Data" />
    </form>

    <script>
        function startDeauth() {
            fetch('/start')
            .then(response => response.text())
            .then(data => {
                document.getElementById("status").innerText = data;
            });
        }
    </script>

</body>
</html>
"""

# Home Page
@app.route('/')
def home():
    return html_page

# Fake Deauth Simulation
@app.route('/start')
def start():
    print("Deauth Simulation Triggered!")
    return "✅ Deauth simulation started (fake)"

# Receive Form Data
@app.route('/submit', methods=['POST'])
def submit():
    global last_received_data

    userdata = request.form.get('userdata')

    if userdata:
        last_received_data = userdata

        print("Received Data:", last_received_data)

        return f"""
        <h2>Data Received:</h2>
        <p>{last_received_data}</p>
        <a href="/">Go Back</a>
        """
    else:
        return "Bad Request: No userdata", 400

# Run Server
if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
