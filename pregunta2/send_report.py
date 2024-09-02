# Funcion para enviar email usando protocolo SMTP fue sacada de la página RealPython
import smtplib
from email.mime.text import MIMEText

with open("reporte.txt", "r") as textfile:
    content = textfile.readlines()
    email_body = "".join(content) # new line characters will be included
    textfile.close()
print("hola")
print(email_body)

subject = "Email Subject"
sender = "sender@gmail.com"
recipients = ["recipient1@gmail.com", "recipient2@gmail.com"]
password = "password"

# Funcion para enviar email
def enviar_email(subject, body, sender, recipients, password):
    msg = MIMEText(body)
    msg['Subject'] = subject
    msg['From'] = sender
    msg['To'] = ', '.join(recipients)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp_server:
       smtp_server.login(sender, password)
       smtp_server.sendmail(sender, recipients, msg.as_string())
    print("Message sent!")

enviar_email(subject, email_body, sender, recipients, password)
