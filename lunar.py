import os
import re

def main():
    # Get Saves
    root_path = r"C:/Program Files (x86)/Steam/userdata/"
    recent_user = os.listdir(root_path)[0]
    ror_base = r"632360/remote/UserProfiles"

    save_dir = os.path.join(root_path, recent_user, ror_base)

    for save in os.listdir(save_dir):
        save_path = os.path.join(save_dir, save)
        replace_lunars(save_path)

def replace_lunars(save_path: str):
    with open(save_path, "r+") as fh:
        xml = fh.read()
        regex = r"<coins>([0-9]+)</coins>"
        coins = re.sub(regex, "<coins>2147483640</coins>", xml)

        fh.write(coins)

if __name__ == "__main__":
    main()