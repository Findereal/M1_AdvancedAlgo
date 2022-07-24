import sys

import numpy as np


class Tabu:
    def __init__(self, k):
        self.size = k
        self.cont = []

    def __repr__(self):
        return str(self.cont)

    def __len__(self):
        return len(self.cont)

    def __contains__(self, item):
        return item in self.cont

    def take(self):
        return self.cont.pop(0)

    def add(self, el):
        self.cont.append(el)
        while len(self.cont) > self.size:
            self.take()


def readf(fn):
    with open(fn) as f:
        lines = f.readlines()
        ltown = []
        n = int(lines[0])
        for i in lines[1:]:
            i = i.split()
            ltown.append((int(i[1]), int(i[2])))
    return n, ltown


def dist_n(n):
    def dist_l(l):
        res = np.sqrt((l[0][0]) ** 2 + (l[0][1]) ** 2)
        for i in range(n - 1):
            a = np.array(l[i])
            b = np.array(l[i + 1])
            # res += np.sqrt((l[i][0] - l[i + 1][0]) ** 2 + (l[i][1] - l[i + 1][1]) ** 2)
            res += np.linalg.norm(a - b)
        return float(np.round(res + np.sqrt((l[-1][0]) ** 2 + (l[-1][1]) ** 2), 2))

    return dist_l


def dist(n, l):
    """
    returns euclidian distance in kilometers of a list of cities visited
    :param l: list of (x,y) tuples
    :return: sum of the distance between each city in the list
    """
    # res = np.sqrt((l[0][0]) ** 2 + (l[0][1]) ** 2)
    # for i in range(n - 1):
    #     a = np.array(l[i])
    #     b = np.array(l[i + 1])
    #     # res += np.sqrt((l[i][0] - l[i + 1][0]) ** 2 + (l[i][1] - l[i + 1][1]) ** 2)
    #     res += np.linalg.norm(a - b)
    # return res + np.sqrt((l[-1][0]) ** 2 + (l[-1][1]) ** 2)
    return dist_n(n)(l)


def sol0(n0, l0):
    n = n0
    l = l0[:]
    res = []
    while n > 0:
        res.append(l.pop(np.random.randint(n)))
        n -= 1
    return res


def perm(l0, a, b):
    l = l0[:]
    l[a], l[b] = l[b], l[a]
    return l


def lperm(l0):
    n = len(l0)
    res = []
    for i in range(n - 1):
        for j in range(i + 1, n):
            res.append(perm(l0, i, j))
    return res


def bestN(l0):
    n = len(l0)
    neigh = lperm(l0)
    # print("    perm done")
    # best = [neigh[0]]
    # d = list(map(dist_n(n), neigh[1:]))
    # for i in range(len(neigh[1:])):
    #     dbest = dist(n, best[0])
    #     curr = neigh[1:][i]
    #     if d[i] < dbest:
    #         best = [curr]
    #     elif d[i] == dbest:
    #         best.append(curr)
    evN = list(map(dist_n(n), neigh))
    bestEV = min(evN)
    res = [neigh[i] for i in range(len(evN)) if evN[i] == bestEV]
    # print("    bestn found")
    return res[np.random.randint(len(res))]


def hillClimb(n, s, maxdep, ltown):
    heur = lambda x, y: dist(n, x) < dist(n, y)
    nbmoves = 0
    # print("  initial solution:", [0] + [ltown.index(i) + 1 for i in s] + [0])
    while nbmoves <= maxdep:
        # print("  nbmoves:", nbmoves)
        news = bestN(s)
        if heur(news, s):
            s = news
        else:
            break
        nbmoves += 1
    # print("  nb moves final:", nbmoves)
    # print("  local optimum found:", [0] + [ltown.index(i) + 1 for i in s] + [0], "\n  value :", dist(n, s))
    return s


def av_hill(n, maxdep, ltown):
    s = 0
    for i in range(100):
        s0 = sol0(n, ltown)
        s += hillClimb(n, s0, maxdep, ltown)[1]
    s /= 100
    return float(np.round(s, 2))


def hillClimbs(n, ltown, maxdep, maxtry):
    heur = lambda x, y: dist(n, x) < dist(n, y)
    nbtry = 1
    # print("Try nb", nbtry)
    s = hillClimb(n, sol0(n, ltown), maxdep, ltown)
    while nbtry < maxtry:
        nbtry += 1
        # print("Try nb", nbtry)
        news = hillClimb(n, sol0(n, ltown), maxdep, ltown)
        if heur(news, s):
            s = news

    # constructs the list of town indexes
    res = [ltown.index(i) + 1 for i in s]
    return [0] + res + [0], dist(n, s)


def av_hills(n, maxdep, maxtry, ltown):
    s = 0
    for i in range(100):
        s += hillClimbs(n, ltown, maxdep, maxtry)[1]
    s /= 100
    return float(np.round(s, 2))


def tabu(n, l0, k, maxmoves=15):
    heur = lambda x, y: dist(n, x) < dist(n, y)

    # print("\nTabu algo:")
    # print("init sol:", [0] + [l0.index(i) + 1 for i in l0] + [0])

    def nonTabuNeighbor(tl: Tabu, l):
        """
        returns the non tabu neighbors of a solution
        :param tl: tabu list
        :param l: list of neighbors of a solution
        :return: neighbors that are not in the tabu list
        """
        ntl = []
        for i in l:
            if not i in tl:
                ntl.append(i)
        return ntl

    tl = Tabu(k)
    bests = l0[:]
    news = l0[:]
    l = l0[:]
    nbmoves = 0
    stop = False
    while nbmoves < maxmoves and not stop:
        # create the neighbors list

        neighlist = lperm(l)
        # print("  lperm done")
        # create the non tabu neighbor list (see up)
        ntl = nonTabuNeighbor(tl, neighlist)
        # print("  ntl done")
        if ntl:
            # this block takes the best neighbor of the current solution
            # print("    eval start")
            evN = list(map(dist_n(n), ntl))
            # print("    eval done")
            bestEV = min(evN)
            res = [ntl[i] for i in range(len(evN)) if evN[i] == bestEV]
            news = res[np.random.randint(len(res))]
            # print("    news generated")
        else:
            # if all the neighbors are already in the tabu list (=> we explored them already)
            # print("    ntl empty")
            stop = True
        tl.add(l)
        if heur(news, bests):
            bests = news
        l = news
        nbmoves += 1
    # print("end sol:", [0] + [l0.index(i) + 1 for i in l] + [0])
    # print("nbmoves", nbmoves)
    coordtl = []
    for i in tl.cont:
        coordtl.append([0] + [l0.index(j) + 1 for j in i] + [0])

    # print("tabu list", coordtl)
    return [0] + [l0.index(i) + 1 for i in bests] + [0], dist(n, bests)


def av_tabu(n, maxdep, ltown, k):
    s = 0
    for i in range(100):
        s0 = sol0(n, ltown)
        s += tabu(n, s0, k, maxdep)[1]
    s /= 100
    return float(np.round(s, 2))


from numpy.linalg import norm


def opt2(l0, i, j):
    l=l0[:]
    if norm(np.array(l[i]) - np.array(l[i + 1])) + norm(np.array(l[j]) - np.array(l[j + 1])) > norm(np.array(l[i]) - np.array(l[j])) + norm(np.array(l[i + 1]) - np.array(l[j + 1])):
        perm(l, i + 1, j)
        l[i + 2:j] = [l[k] for k in range(j - 1, i + 1, -1)]
    return l


def perm2(l):
    n = len(l)
    res = []
    for i in range(n - 4):
        for j in range(i + 3, n - 1):
            res.append(opt2(l, i, j))
    return res

def best2(l0):
    n = len(l0)
    neigh = perm2(l0)
    evN = list(map(dist_n(n), neigh))
    bestEV = min(evN)
    res = [neigh[i] for i in range(len(evN)) if evN[i] == bestEV]
    # print("    bestn found")
    return res[np.random.randint(len(res))]

def main():
    args = sys.argv[1:]
    if not args:
        print("testetstsetestsetstest")
        # t5 = readf("tsp5.txt")
        # print("hillclimb on tsp5:", hillClimbs(*t5, 15, 5))
        # print("tabu on tsp5:", tabu(*t5, 6,50))
        # #t101 = readf("tsp101.txt")
        # print("\ntabu on tsp101:", tabu(*t101, 30, 150))
        # print("hillclimb on tsp101:", hillClimbs(*t101, 50, 30))
    else:
        for i in args:
            tsp = readf(i)
            print("hillclimb:", hillClimbs(*tsp, 100, 50))
            print("tabu:", tabu(*tsp, 6))


if __name__ == "__main__":
    main()

# _____$$$$__________$$$$$
# ___$$$$$$$$______$$$$$$$$$
# __$$$$$$$$$$____$$$$$$$$$$$
# _$$$$$$$$$$$$__$$$$$$$$$$$$$
# _$$$$$$$$$$$$$_$$$$$$$$$$$$$
# $$$$$$$$$$$$$$$$$$$$$$$$$$$$
# $$$$$$$$$$$$$$$$$$$$$$$$$$$$$
# $$$$$$$$$$$$$$$$$$$$$$$$$$$$$_$$$$
# $$$$$$$$$$$$$$$$$_____$$$$$$$______$
# $$$$$$$$$$$$$$$$________$$$$________$
# _$$$$$$$$$$$$$$__________$$__________$
# _$$$$$$$$$$$$$___________$___________$
# _$$$$$$$$$$$$$_______________________$
# __$$$$$$$$$$$$_______________________$
# ___$$$$$$$$$$$_______________________$
# ____$$$$$$$$$$_______________________$
# _____$$$$$$$$$_______________________$
# ______$$$$__$$$__$$$$$_______________$
# _______$______$_$_____$_____________$
# ______$_______$$______$_____________$
# ______$________________$___________$
# ______$________________$__________$
# _______$_______________$_________$
# _______$______________$_________$
# ________$_____________$________$
# _________$___________$$______$
# __________$_________$__$____$
# ___________$_______$_____$$
# ____________$$___$$
# ______________$$$
# _______________$
# >loveyou.png
