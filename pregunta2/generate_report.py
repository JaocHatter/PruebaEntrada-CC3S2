import os

# Esta funcion nos permite hallar el status de nuestra operacion
# Y las estadisticas despues de 5 paquetes transmitidos

def getstatusoutput(cmd):
    """Return (status, output) of executing cmd in a shell."""
    pipe = os.popen('{ ' + cmd + '; } 2>&1', 'r')
    text = pipe.read()
    pipe.close()
    sts = pipe.close()
    if sts is None: sts = 0
    if text[-1:] == '\n': text = text[:-1]
    return sts, text

print("Ingrese ip(s): ")

ip_address = input() 
status,text = getstatusoutput("ping -c 5 "+ip_address)

print(status)
print(text)

# Separamas por saltos de linea
lineas = text.splitlines()
for line in lineas:
    if "rtt min/avg/max/mdev" in line:
        stats = line.split("=")[1].strip()
        min_rtt, avg_rtt, max_rtt, mdev_rtt = stats.split("/")
        break

print(f"Ping a {ip_address}:")
print(f"Min RTT: {min_rtt} ms")
print(f"Avg RTT: {avg_rtt} ms")
print(f"Max RTT: {max_rtt} ms")
print(f"Mdev RTT: {mdev_rtt} ms")

file = open("reporte.txt","a")
file.write(text)
file.close()


