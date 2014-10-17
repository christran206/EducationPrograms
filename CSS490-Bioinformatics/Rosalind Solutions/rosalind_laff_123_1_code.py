__author__ = 'Christopher'

def local_alignment_affine_gap_penalty(v, w, scoring_matrix, sigma, epsilon):

    # Initialize the matrices with zero as the minimum score
    S_lower = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]
    S_middle = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]
    S_upper = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]
    backtrack = [[0 for j in xrange(len(w)+1)] for i in xrange(len(v)+1)]

    # Initialize the maximum score below the lowest possible score.
    max_score = -1
    max_i, max_j = 0, 0

    # Fill in the Score and Backtrack matrices.
    # Calculate by row
    for i in xrange(1, len(v)+1):
        for j in xrange(1, len(w)+1):
            S_lower[i][j] = max([S_lower[i-1][j] - epsilon, S_middle[i-1][j] - sigma])
            S_upper[i][j] = max([S_upper[i][j-1] - epsilon, S_middle[i][j-1] - sigma])
            middle_scores = [S_lower[i][j], S_middle[i-1][j-1] + scoring_matrix[v[i-1], w[j-1]], S_upper[i][j], 0]
            S_middle[i][j] = max(middle_scores)
            backtrack[i][j] = middle_scores.index(S_middle[i][j])

            if S_middle[i][j] > max_score:
                max_score = S_middle[i][j]
                max_i, max_j = i, j

    # Initialize the indices to start at the position of the high score.
    i, j = max_i, max_j

    # Initialize the aligned strings as the input strings up to the position of the high score.
    v_aligned, w_aligned = v[:i], w[:j]

    # Backtrack to start of the local alignment starting at the highest scoring cell.
    # Note: the solution format specifically asks for substrings, so no indel insertion necessary.
    while backtrack[i][j] != 3 and i*j != 0:
        if backtrack[i][j] == 0:
            i -= 1
        elif backtrack[i][j] == 1:
            i -= 1
            j -= 1
        elif backtrack[i][j] == 2:
            j -= 1

    # Cut the strings at the ending point of the backtrack.
    v_aligned = v_aligned[i:]
    w_aligned = w_aligned[j:]

    return str(max_score), v_aligned, w_aligned

if __name__ == '__main__':

    blosum62 = infile = open("BLOSUM62.txt", 'r')
    scoring_matrix = {}
    for score in blosum62:
        #print(score)
        source, destination, num = score.split(' ',2)
        scoring_matrix[(source,destination)] = int(num)

    infile = open(raw_input("Name of text file: "), 'r')
    lines = (line.rstrip('\n') for line in infile)

    string = []
    count = -1
    for line in lines:
        if line[0] == '>':
            count += 1
            string.append("")
        else:
            string[count] += line

    alignment = local_alignment_affine_gap_penalty(string[0], string[1], scoring_matrix,11,1)
    print '\n'.join(alignment)