void hanoi(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        cout << "Move disk 1 from " << from << " to " << to << endl;
    }
    else
    {
        hanoi(n - 1, from, aux, to);

        cout << "Move disk " << n << " from " << from << " to " << to << endl;

        hanoi(n - 1, aux, to, from);
    }

}
moves(n) = 2^n - 1

	| Disks | Moves |
| ----- | ----- |
| 1     | 1     |
| 2     | 3     |
| 3     | 7     |
| 4     | 15    |
| 5     | 31    |
big 0^10:
