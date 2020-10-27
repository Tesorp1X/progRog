package com.codeforces;

import java.util.Scanner;

public class TheatreSquare {

    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        long n = in.nextInt();
        long m = in.nextInt();
        long a = in.nextInt();
        in.close();

        long flagstone_n = 0, flagstone_m = 0;
        long n_amount = 0, m_amount = 0;


        /** Slow solution
        while ((n_amount * m_amount * a < n * m) && (flagstone_n < n || flagstone_m < m)) {
            if (flagstone_n < n) {
                ++n_amount;
                flagstone_n += a;
            }
            if (flagstone_m < m){
                ++m_amount;
                flagstone_m += a;
            }

        }
        System.out.println(n_amount * m_amount);*/

        /** Fast solution! */
        System.out.println((long)(Math.ceil((double)((m + a - 1) / a)) * Math.ceil((double)((n + a - 1) / a))));
    }
}
