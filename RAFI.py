from flask import Flask, request, Response
import json

app = Flask(__name__)


temp_list = []

@app.route('/')
def hello():
    return 'WELCOME TO MY API'

@app.route('/sensor/wibu', methods=["POST", "GET"])
def sensor():
    if request.method == 'POST':
        data = request.get_json()
        temperature = data["temperature"]
        kelembapan = data["humidity"]
        timestamp = data["timestamp"]

        temp_list.append([temperature, kelembapan, timestamp])

        data = {
            'message': 'Data saved successfully'
        }
    else: 
        data = {
            'temperature_list': temp_list
        }

    response = Response(
        json.dumps(data),
        status=200,
        mimetype='application/json'
    )

    return response

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')