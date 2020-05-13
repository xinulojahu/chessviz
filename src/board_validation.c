
int iswhite(char c)
{
    switch (c) {
    case 'P':
    case 'Q':
    case 'K':
    case 'R':
    case 'B':
    case 'N':
        return 1;
    default:
        return 0;
    }
}

int isblack(char c)
{
    return iswhite(c + 'A' - 'a');
}

int ischessman(char c)
{
    return iswhite(c) || isblack(c);
}
