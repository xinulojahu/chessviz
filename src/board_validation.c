int isboardletter(char c)
{
    if ((c >= 'a') && (c <= 'h')) {
        return 1;
    }
    return 0;
}

int isboarddigit(char c)
{
    if ((c >= '1') && (c <= '8')) {
        return 1;
    }
    return 0;
}

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
