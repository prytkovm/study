class FileProcess:

    @staticmethod
    def read(path):
        try:
            with open(path, "r") as f:
                data = f.readlines()
                for item in data:
                    result = item.rstrip("\n").split("-")
                    yield result
        except FileNotFoundError:
            raise FileNotFoundError("File not found")

    @staticmethod
    def write(path, data):
        try:
            with open(path, "w") as f:
                for item in data:
                    f.write(str(item[1]) + "-" + str(item[2]) + "-" + str(item[0]) + "\n")
        except FileNotFoundError:
            raise FileNotFoundError("File not found")
