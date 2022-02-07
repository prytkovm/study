import libnum
from time import time


class RSA:

    def __init__(self, prime_len=15):
        """Параметр prime_len отвечает за кол-во разрядов в генерируемом простом числе (в двоичном представлении),
        по умолчанию 15"""
        # Cгенерируем два различных простых 15-разрядных числа
        # p и q, произведение которых послужит модулем для публичного и приватного ключей,
        # вычислим значение функции Эйлера от модуля и экспоненту для публичного и приватного ключей
        self.p = libnum.generate_prime(prime_len, k=25)
        self.q = libnum.generate_prime(prime_len, k=25)
        # Исключим совпадение сгенерированных простых чисел
        while self.p == self.q:
            self.p = libnum.generate_prime(prime_len, k=25)
            self.q = libnum.generate_prime(prime_len, k=25)
        self.module = self.p * self.q
        self.phi = self.__euler_func__(self.p, self.q)
        self.public_key = self.__create_public_key__()
        self.private_key = self.__create_private_key__()

    def __create_public_key__(self):
        # Публичная экспонента - число e, взаимно простое с значением ф-и
        # Эйлера от сгенерированного модуля n, такое что 1 < e < f(n)
        public_exponent = libnum.generate_prime(len(str(self.phi)), k=25)
        return dict(exponent=public_exponent, module=self.module)

    def __create_private_key__(self):
        # Приватная экспонента - число d, обратное к публичной экспоненте e в
        # кольце вычетов по модулю f(n), где n - сгенерированный модуль,
        # f(n) - значение функции Эйлера от модуля
        private_exponent = pow(self.public_key['exponent'], -1, self.phi)
        return dict(exponent=private_exponent, module=self.module)

    def __euler_func__(self, num1, num2):
        # Используем свойство ф-и Эйлера: значение ф-и от взаимно простых
        # чисел есть произведение значений ф-и от каждого из чисел,
        # а значение ф-и f от простого числа p: f(p) = p - 1
        return (num1 - 1) * (num2 - 1)

    def encrypt(self, msg, key):
        # Для удобства будем представлять зашифрованное сообщение в виде
        # списка чисел x, где x - порядковый номер символа в сообщении msg по таблице
        # ASCII,
        # возведенный в степень e(публичная экспонента получателя) по модулю
        # публичного ключа получателя
        encrypted = [pow(ord(char), key["exponent"], key["module"]) for char in msg]
        return encrypted

    def decrypt(self, encrypted_msg):
        # Для расшифровки полученного сообщения возвродим каждый
        # зашифрованный символ в степень d (приватная экспонента) по модулю n своего
        # приватного ключа,
        # после чего сопоставляем полученное число символу в таблице ASCII
        decrypted = [chr(pow(char, self.private_key["exponent"],
                             self.private_key["module"])) for char in encrypted_msg]
        return ''.join(decrypted)


class Attack:

    def encrypt(self, key, msg):
        # Реализация функции для шифрования перехваченного шифротекста
        encrypted = [(pow(item, key["exponent"], key["module"])) for item in msg]
        return encrypted

    def cyclic_attack(self, key, ciphertext):
        # Производим шифрование перехваченного шифротекста пока не получим этот же шифротекст,
        # запоминая значение на предыдущем шаге. Как только мы получили изначальный шифротекст -
        # возвращаем значение предыдущего шага, это и будет исходный текст
        cycles = 1
        temp = self.encrypt(key, ciphertext)
        cracked_msg = []
        while temp != ciphertext:
            cracked_msg = temp
            temp = self.encrypt(key, temp)
            cycles += 1
        return ''.join(chr(cracked_char) for cracked_char in cracked_msg), cycles


if __name__ == "__main__":
    # Пусть у нас есть два персонажа - Алиса и Боб. Алиса хочет отправить
    # Бобу сообщение, предварительно зашифровав его при помощи RSA.
    # Для этого она берет сообщенный ей Бобом публичный ключ и шифрует
    # отправляемое сообщение.
    # После того, как Боб получает сообщение Алисы, он производит
    # расшифровку, используя свой приватный ключ.
    Alice = RSA()
    Bob = RSA()
    encrypted_msg = Alice.encrypt("Hello from ETU!", Bob.public_key)
    decrypted = Bob.decrypt(encrypted_msg)
    print("Encrypted:{}\n Decrypted: {}\n".format(encrypted_msg, decrypted))
    Crack = Attack()
    start = time()
    cracked, cycles = Crack.cyclic_attack(Bob.public_key, encrypted_msg)
    end = time()
    print("Cracked: {}\n Cycles ran: {}\n Time taken: {}\n".format(cracked, cycles, end-start))
