package com.codeforces;

import java.io.*;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class HelpfulMaths {


    private static class MyArrayList<E> extends ArrayList<E> {

        public MyArrayList() {
            super();
        }

        @Override
        public String toString() {

            Iterator<E> it = iterator();
            if (!it.hasNext()) {
                return "";
            }
            StringBuilder sb = new StringBuilder();
            for (;;) {
                E e = it.next();
                sb.append(e);
                if (it.hasNext()) {
                    sb.append("+");
                } else {
                    break;
                }
            }
            return sb.toString();
        }
    }

    public static void main(String[] args) throws IOException {

        List<Integer> inputArray = new MyArrayList<>();
        InputStream inputStream = System.in;

        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String string = reader.readLine();
        String[] splited_input =  string.split("[+]");

        for (var str : splited_input) {
            inputArray.add(Integer.parseInt(str));
        }
        inputArray.sort(Integer::compareTo);
        String res = inputArray.toString();
        System.out.println(res);

    }


}
