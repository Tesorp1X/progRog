package com.codeforces;

import java.util.Scanner;

public class StringTask {
    public static void main(String[] args) {

        Scanner in = new Scanner(System.in);
        String str = in.nextLine();
        in.close();

        String result = str.toLowerCase().replaceAll("[aoyeui]", "");
        System.out.println(result);

    }
}
