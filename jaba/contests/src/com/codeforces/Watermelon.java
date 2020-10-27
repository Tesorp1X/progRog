package com.codeforces;


import java.util.Scanner;

public class Watermelon {

    public static void main(String[] args) {


        Scanner in = new Scanner(System.in);
        int weight = in.nextInt();
        in.close();

        if (weight == 2) {

            System.out.println("NO");

        } else if (weight % 2 == 1) {

            System.out.println("NO");

        } else {

            System.out.println("YES");

        }



    }
}
