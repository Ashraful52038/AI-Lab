public class Maze {
    public static void main(String[] args) {
        System.out.println(count(3, 3));
    }

    static int count(int r,int c)
    {
        if(r==1 || c==1)
        {
            return 1;
        }

        int right=count(r, c-1);
        int down=count(r-1, c);

        return down+right;
    }
}
