def edit_alignment(v, w):
    '''Returns the edit score and edit alignment of strings v and w.'''
    from numpy import zeros

    # Initialize the matrices.
    S = zeros((len(v)+1, len(w)+1), dtype=int)
    backtrack = zeros((len(v)+1, len(w)+1), dtype=int)

    for i in xrange(1, len(v)+1):
        S[i][0] = i
    for j in xrange(1, len(w)+1):
        S[0][j] = j

    # Fill in the Score and Backtrack matrices.
    for i in xrange(1, len(v)+1):
        for j in xrange(1, len(w)+1):
            scores = [S[i-1][j-1] + (v[i-1] != w[j-1]), S[i-1][j]+1, S[i][j-1]+1]
            S[i][j] = min(scores)
            backtrack[i][j] = scores.index(S[i][j])

    # Quick lambda function to insert indels.
    insert_indel = lambda word, i: word[:i] + '-' + word[i:]

    # Initialize the aligned strings as the input strings.
    v_aligned, w_aligned = v, w

    # Initialize the values of i,j and get the minimum score.
    i,j = len(v), len(w)
    min_score = S[i][j]

    # Backtrack to the edge of the matrix starting bottom right.
    while i*j != 0:
        if backtrack[i][j] == 1:
            i -= 1
            w_aligned = insert_indel(w_aligned, j)
        elif backtrack[i][j] == 2:
            j -= 1
            v_aligned = insert_indel(v_aligned, i)
        else:
            i -= 1
            j -= 1

    # Prepend the necessary preceeding indels to get to (0,0).
    for repeat in xrange(i):
        w_aligned = insert_indel(w_aligned, 0)
    for repeat in xrange(j):
        v_aligned = insert_indel(v_aligned, 0)

    return str(min_score), v_aligned, w_aligned

if __name__ == '__main__':

    print("Takes in a Rosalind FASTA file and computes two lines for Edit Alignment")

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


    # Get the edit alignment.
    edited = edit_alignment(string[0], string[1])

    # Print and save the answer.
    print '\n'.join(edited)