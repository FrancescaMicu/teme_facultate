package org.example;

import java.util.HashMap;

public class Student implements Comparable<Student> {
    //  declarare campuri
    private String name;
    private String group;
    private HashMap<String,Double> exams;

    //  constructor
    public Student(String name, String group) {
        this.name = name;
        this.group = group;
        this.exams = new HashMap<>();
    }

    //  settere si gettere
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public String getGroup() {
        return group;
    }
    public void setGroup(String group) {
        this.group = group;
    }
    public void addExam(String nameExam, Double score) {
        exams.put(nameExam, score);
    }
    public HashMap<String, Double> getExams() {
        return exams;
    }

    //  metoda pentru obtinerea punctajului de la un examen
    public double calcScoreCurrExam(String nameExam) {
        return exams.get(nameExam);
    }

    //  metoda pentru setarea punctajului
    public void setScore(String nameExam, Double score) {
        exams.put(nameExam, score);
    }

    //  metoda de comparare pentru sortare
    public int compareTo(Student student) {
        if (this.getName().compareTo(student.getName()) > 0) {
            return 1;
        } else if (this.getName().compareTo(student.getName()) < 0) {
            return -1;
        }
        return 0;
    }

    //  metode pentru pentru a identifica studentii unici după nume
    //  pentru functionarea corecta a cheilor in HashMap
    @Override
    public boolean equals(Object obj) {
        if (obj == null || name == null || obj.getClass() != Student.class) {
            return false;
        }
        if (name.equals(((Student)obj).name)) {
            return true;
        }
        return false;
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }
}
