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


def readToMatrix(filename):
    with open(filename) as f:
        lines = f.readlines()
        l = lines[0].split()
        size = int(l[0])
        p = int(l[1])
        m = np.zeros((size, size))
        for i in range(size):
            for j in range(size):
                m[i, j] = l[i * size + j + 2]
    return m, p


def sol0(n):
    return [np.random.randint(0, 2) for i in range(n)]


def eval_q(q):
    def eval_sol(sol):
        n = len(sol)
        res = 0
        for i in range(n):
            for j in range(n):
                res += q[i, j] * sol[i] * sol[j]
        return res

    return eval_sol


def eval(q, sol):
    return eval_q(q)(sol)


def bestN(sol, q):
    neigeList = [[(sol[j] + 1) % 2 if j == i else sol[j] for j in range(len(sol))] for i in range(len(sol))]
    evNL = list(map(eval_q(q), neigeList))
    bestEV = min(evNL)
    res = [neigeList[i] for i in range(len(evNL)) if evNL[i] == bestEV]
    index = np.random.randint(len(res))
    return res[index]


def hillClimb(s, maxdep, q):
    heur = lambda x, y: eval(q, x) < eval(q, y)
    nbmoves = 0
    while nbmoves <= maxdep:
        news = bestN(s, q)
        if heur(news, s):
            s = news
        else:
            break
        nbmoves += 1
    # print(nbmoves)
    return s,nbmoves


def hillClimbs(maxdep, maxtry, q):
    heur = lambda x, y: eval(q, x) < eval(q, y)
    nbtry = 1
    s0=sol0(len(q[0]))
    (s,nm) = hillClimb(s0, maxdep, q)
    nmb=nm
    bests0=s0
    while nbtry < maxtry:
        s0=sol0(len(q[0]))
        (news,nm) = hillClimb(s0, maxdep, q)
        if heur(news, s):
            bests0=s0
            s = news
            nmb=nm
        nbtry += 1
    print(bests0,nmb)
    return s


def tabu(s, k, q, maxmoves=15):
    heur = lambda x, y: eval(q, x) < eval(q, y)

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
    bests = s
    news = s
    nbmoves = 0
    stop = False
    while nbmoves < maxmoves and not stop:
        # create the neighbors list
        neighlist = [[(s[j] + 1) % 2 if j == i else s[j] for j in range(len(s))] for i in range(len(s))]
        # create the non tabu neighbor list (see up)
        ntl = nonTabuNeighbor(tl, neighlist)
        if ntl:
            # this block takes the best neighbor of the current solution
            evN = list(map(eval_q(q), ntl))
            bestEV = min(evN)
            res = [ntl[i] for i in range(len(evN)) if evN[i] == bestEV]
            news = res[np.random.randint(len(res))]
        else:
            # if all the neighbors are already in the tabu list (=> we explored them already)
            stop = True
        tl.add(s)
        if heur(news, bests):
            bests = news
        s = news
        nbmoves += 1
    print(nbmoves)
    print(tl.cont[0])
    return bests


def bestNv2(sol, q, p):
    neigeList = [[(sol[j] + 1) % 2 if j == i else sol[j] for j in range(len(sol))] for i in range(len(sol))]
    pneiglist = [i for i in neigeList if sum(i) >= p]
    evNL = list(map(eval_q(q), pneiglist))
    bestEV = min(evNL)
    res = [pneiglist[i] for i in range(len(evNL)) if evNL[i] == bestEV]
    index = np.random.randint(len(res))
    return res[index]


def hillClimbv2(s, maxdep, q, p):
    heur = lambda x, y: eval(q, x) < eval(q, y)
    nbmoves = 0
    while nbmoves <= maxdep:
        news = bestNv2(s, q, p)
        if heur(news, s):
            s = news
        else:
            break
        nbmoves += 1
    return s


def hillClimbsv2(maxdep, maxtry, q, p):
    heur = lambda x, y: eval(q, x) < eval(q, y)
    nbtry = 1
    s = hillClimbv2(sol0(len(q[0])), maxdep, q, p)
    while nbtry < maxtry:
        news = hillClimb(sol0(len(q[0])), maxdep, q)
        if heur(news, s):
            s = news
        nbtry += 1

    return s


def main():
    args = sys.argv[1:]
    print(args)
    if not args:
        print("hello")
    #     p6 = 'partition6.txt'
    #     g12345 = 'graphe12345.txt'
    #
    #     (qmat_p6, pp6) = readToMatrix(p6)
    #     (qmat_graph, pgraph) = readToMatrix(g12345)
    #
    #     s_p6 = hillClimbs(25, 10, qmat_p6)
    #     print("v1 p: ", s_p6, eval(qmat_p6, s_p6))
    #     s_graph = hillClimbs(25, 10, qmat_graph)
    #     print("v1 g: ", s_graph, eval(qmat_graph, s_graph))
    #
    #     s_p6_tabu = tabu(sol0(len(qmat_p6[0])), 5, qmat_p6)
    #     print("tabu p: ", s_p6_tabu, eval(qmat_p6, s_p6_tabu))
    #     s_g_tabu = tabu(sol0(len(qmat_graph[0])), 15, qmat_graph)
    #     print("tabu g: ", s_g_tabu, eval(qmat_graph, s_g_tabu))
    #
    #     s_p6v2 = hillClimbsv2(25, 10, qmat_p6, pp6)
    #     print("v2 p: ", s_p6v2, eval(qmat_p6, s_p6v2))
    #     s_graph = hillClimbsv2(25, 10, qmat_graph, pgraph)
    #     print("v2 g: ", s_graph, eval(qmat_graph, s_graph))

    elif len(args) == 1:
        fn = args[0]
        (q, p) = readToMatrix(fn)

        sv1 = hillClimbs(30, 20, q)
        print("v1:", sv1, eval(q, sv1))

        st = tabu(sol0(len(q[0])), 5, q)
        print("tabu:", st, eval(q, st))

        sv2 = hillClimbsv2(30, 20, q, p)
        print("v2:", sv2, eval(q, sv2))
    else:
        for i in args:
            (q, p) = readToMatrix(i)
            sv1 = hillClimbs(30, 20, q)
            print("v1:", sv1, eval(q, sv1))

            st = tabu(sol0(len(q[0])), 5, q)
            print("tabu:", st, eval(q, st))

            sv2 = hillClimbsv2(30, 20, q, p)
            print("v2:", sv2, eval(q, sv2))


if __name__ == "__main__":
    main()
