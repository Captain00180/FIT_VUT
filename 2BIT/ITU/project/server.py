from flask import Flask, request, jsonify
from backend import user

app = Flask(__name__)


@app.route('/api/', methods=["POST", "GET"])
def main_interface():
    response = request.get_json()
#    print (response["message"])

    if response is not None:
        print((response["key"]))

    return jsonify(response)


@app.route('/api/getData', methods=['GET'])
def get_data():
    return jsonify(player.getData())


@app.route('/api/setData', methods=['POST'])
def set_data():
    data = request.get_json()
    return jsonify("Success")


if __name__ == '__main__':
    app.run()




