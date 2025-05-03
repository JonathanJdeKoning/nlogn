import subprocess
from random import randint


while True:
    case = [randint(0, 100) for _ in range(randint(4000, 4000))]
    answers = []
    N = len(case)
    for op in "JD":
        s = " ".join([str(num) for num in case])
        command = "./a.out " +op + " " + str(N) + " " + s
        p = subprocess.Popen(command, stdout=subprocess.PIPE, shell=True)

        ans, _= p.communicate()

        p_status = p.wait()
        answers.append(int(ans))
        print(op, ans.strip())
    if len(set(answers)) != 1:
        print(case)
        print(answers)
        exit()
