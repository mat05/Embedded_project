import requests


api_key = '5660801'
phone_number = '+33650404433'
message = 'This is a new test message'

params = {'source': 'web', 'phone': phone_number, 'text': message, 'apikey': api_key}
url = 'https://api.callmebot.com/whatsapp.php'

response = requests.get(url, params=params)
print(response)
if response.status_code == 200:
    print("message sent")
else:
    print("ko")
