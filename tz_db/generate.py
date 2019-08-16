import sys
import os
import jinja2
import zlib

loader = jinja2.FileSystemLoader(".")
template_env = jinja2.Environment(loader=loader)
template_name = sys.argv[1]
template = template_env.get_template("{}.template".format(template_name))

def chunks(l, n):
    for i in range(0, len(l), n):
        yield l[i:i + n]

def generate_encoding(zonename):
    with open("tzdb/build/usr/share/zoneinfo/" + zonename, "rb") as zone_file:
        binary_data_raw = zone_file.read()
        binary_data_len = len(binary_data_raw)
        data = {
            "full_name": zonename,
            "safe_name": "zone_data_" + zonename.replace("-", "_M_").replace("+", "_P_").replace("/", "_S_"),
            "binary_data_raw": binary_data_raw,
            "binary_data_len": binary_data_len
        }
        return data

def to_hex_codes(data):
    if (sys.version_info > (3, 0)):
        return ",\n".join([", ".join(["0x{:02X}".format(b) for b in chunk]) for chunk in chunks(data, 16)])
    else:
        return ",\n".join([", ".join(["0x{:02X}".format(ord(b)) for b in chunk]) for chunk in chunks(data, 16)])

with open("zn.txt", "r") as timezone_file:
    zones = [line.rstrip() for line in timezone_file.readlines()]

zones.append("posixrules")

zones.sort()

zones = [generate_encoding(zone) for zone in zones]

# collect all binary data into a big array, save the offset in the table
complete_binary_data = []
zone_data_offset = 0
for z in zones:
    z["offset"] = zone_data_offset
    complete_binary_data += z["binary_data_raw"]
    zone_data_offset += z["binary_data_len"]

zone_data_formatted = to_hex_codes(complete_binary_data)
zone_data_compressed = zlib.compress(bytearray(complete_binary_data), 9)
zone_data_compressed_formatted = to_hex_codes(zone_data_compressed)
for z in zones:
    z["binary_data"] = to_hex_codes(z["binary_data_raw"])

with open(template_name, "w") as output_file:
    output = template.render({"zones": zones, "zone_data": zone_data_formatted, "zone_data_compressed": zone_data_compressed_formatted, "zone_data_compressed_len": len(zone_data_compressed)})
    output_file.write(output)

