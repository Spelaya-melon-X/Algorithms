
def build_hypercube(dim):
    total = 1 << dim
    adj = [[] for _ in range(total)]
    for v in range(total):
        for bit in range(dim):
            adj[v].append(v ^ (1 << bit))
    return adj

def stage_one(tree_set, deg_map, graph):
    for x in list(tree_set):
        if deg_map[x] < 2:
            continue
        for y in graph[x]:
            if y not in tree_set:
                tree_set.add(y)
                deg_map[x] += 1
                deg_map[y] = 1
                return True
    return False

def stage_two(tree_set, deg_map, graph):
    for x in list(tree_set):
        outsiders = [y for y in graph[x] if y not in tree_set]
        if len(outsiders) >= 2:
            y1, y2 = outsiders[0], outsiders[1]
            tree_set.update([y1, y2])
            deg_map[x] += 2
            deg_map[y1] = deg_map[y2] = 1
            return True
    return False

def stage_three(tree_set, deg_map, graph, total_vertices):
    for y in range(total_vertices):
        if y in tree_set:
            continue
        parents = [p for p in graph[y] if p in tree_set]
        outsiders = [z for z in graph[y] if z not in tree_set and z != y]
        if parents and len(outsiders) >= 2:
            x = parents[0]
            z1, z2 = outsiders[0], outsiders[1]
            tree_set.update([y, z1, z2])
            deg_map[x] += 1
            deg_map[y] = 3
            deg_map[z1] = deg_map[z2] = 1
            return True
    return False

def stage_four(tree_set, deg_map, graph):
    for x in list(tree_set):
        for y in graph[x]:
            if y not in tree_set:
                tree_set.add(y)
                deg_map[x] += 1
                deg_map[y] = 1
                return True
    return False

def kleitman_west(dim):
    graph = build_hypercube(dim)
    total = 1 << dim
    
    tree_vertices = {0}
    degree = {0: 0}
    
    while len(tree_vertices) < total:
        if stage_one(tree_vertices, degree, graph):
            continue
        if stage_two(tree_vertices, degree, graph):
            continue
        if stage_three(tree_vertices, degree, graph, total):
            continue
        if stage_four(tree_vertices, degree, graph):
            continue
    
    return sum(1 for d in degree.values() if d == 1)

print(f"Итого кол-во висячих вершин равняется: {kleitman_west(6)}")