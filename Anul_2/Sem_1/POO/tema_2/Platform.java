package org.example;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;

public class Platform {
    //  declarare campuri
    private static final DateTimeFormatter timeFormat = DateTimeFormatter.ofPattern("dd-MM-yyyy-HH-mm");
    private HashMap<String, Exam> exams;
    private HashMap<String, Student> students;

    //  constructor
    public Platform() {
        this.exams = new HashMap<>();
        this.students = new HashMap<>();
    }

    //  metoda pentru create_exam
    private void createExam(LocalDateTime timestamp, String nameExam, LocalDateTime startDate, LocalDateTime endDate) {
        Exam newExam = new Exam(timestamp, nameExam, startDate, endDate);
        exams.put(nameExam, newExam);
    }

    //  metoda pentru add_question
    private void addQuestion(LocalDateTime timestamp, String typeQuestion, String nameExam, String author, int difficulty, double maxPoints, String textQuestion, String rightAnswer) {
        Question<?> newQuestion = null;
        if (typeQuestion.equals("open_ended")) {
            newQuestion = new OpenEndedQuestion(timestamp, typeQuestion, author, difficulty, maxPoints, textQuestion, rightAnswer);
        } else if (typeQuestion.equals("fill_in_the_blank")) {
            newQuestion = new FillInTheBlankQuestion(timestamp, typeQuestion, author, difficulty, maxPoints, textQuestion, rightAnswer);
        } else if (typeQuestion.equals("multiple_choice")) {
            ResponseOption respOptRightAns = ResponseOption.valueOf(rightAnswer);
            newQuestion = new MultipleChoiceQuestion(timestamp, typeQuestion, author, difficulty, maxPoints, textQuestion, respOptRightAns);
        } else {
            System.out.println("Eroare - Tip invalid de intrebare");
            return;
        }
        exams.get(nameExam).addQuestion(newQuestion);
    }

    //  metoda pentru list_history_question
    private void listHistoryQuestion(String nameExam, String path, LocalDateTime cmdTimeStamp) {
        try {
            Exam exam = exams.get(nameExam);
            exam.printQuestionsAfterTimestamp(path, cmdTimeStamp);
        } catch (Exception e) {
            System.out.println("Eroare - Nu s-au putut afisa intrebarile dupa data");
        }
    }

    //  metoda pentru print_exam
    private void printExam(String nameExam, String path, LocalDateTime cmdTimeStamp) {
        try {
            Exam exam = exams.get(nameExam);
            exam.printQuestionsAfterDifficulty(path, cmdTimeStamp);
        } catch (Exception e) {
            System.out.println("Eroare - Nu s-au putut afisa intrebarile dupa dificultate");
        }
    }

    //  metoda pentru register_student
    private void registerStudent(String nameStud, String group) {
        Student newStudent = new Student(nameStud, group);
        students.put(nameStud, newStudent);
    }

    //  metoda pentru submit_exam
    private void submitExam(String nameExam, String nameStud, ArrayList<String> answers, LocalDateTime cmdTimeStamp, String path) {
        Student student = students.get(nameStud);
        try {
            double totalPoints = exams.get(nameExam).studAnswersChecked(student, answers, cmdTimeStamp);
            //  setarea scorului studentului si in Platform
            student.setScore(nameExam, totalPoints);
        } catch(SubmissionOutsideTimeIntervalException e1) {
            //  setarea scorului studentului la 0
            student.setScore(nameExam, 0.0);
            try {
                String fileName = path + "console.out";
                PrintWriter writeFile = new PrintWriter(new FileWriter(fileName, true));
                writeFile.println(e1.toString());
                writeFile.close();
            } catch (FileNotFoundException e2) {
                System.out.println("Eroare - Nu s-au putut scrie in fisier raspunsurile studentului");
            } catch (IOException e3) {
                throw new RuntimeException(e3);
            }
        }
    }

    //  metoda show_student_score
    private void showStudentScore(String nameExam, String nameStud, LocalDateTime cmdTimeStamp, String path) {
        Student student = students.get(nameStud);
        Double studScore = student.calcScoreCurrExam(nameExam);
        try {
            String fileName = path + "console.out";
            PrintWriter writeFile = new PrintWriter(new FileWriter(fileName, true));
            writeFile.printf(cmdTimeStamp.format(timeFormat) + " | " + "The score of " + nameStud + " for exam " + nameExam + " is " + "%.2f", studScore);
            writeFile.println();
            writeFile.close();
        } catch (FileNotFoundException e1) {
            System.out.println("Eroare - Nu s-a putut scrie in fisier scorul studentului");
        } catch (IOException e2) {
            throw new RuntimeException(e2);
        }
    }

    //  metoda generate_report
    private void generateReport(String nameExam, String path, LocalDateTime cmdTimeStamp) {
        try {
            exams.get(nameExam).printResultsAnytime(path, cmdTimeStamp);
        } catch (Exception e) {
            System.out.println("Eroare - Nu s-au putut afisa notele studentilor");
        }
    }

    //  metoda pentru identificarea comenzii
    public void interpretCommands(String command, String path) {
        ////////  de vazut daca chiar nu pot DELOC cu array uri simple(la split si la answers!!!!!!)
        //  taierea comenzii in cuvinte
        String[] word = command.split("\\|");

        //  stergerea spatiilor goale de dupa cuvinte
        for (int i = 0; i < word.length; i++) {
            word[i] = word[i].trim();
        }

        //  obtinere timestamp
        LocalDateTime timestamp = LocalDateTime.parse(word[0], timeFormat);

        //  comanda create_exam
        if (word[1].equals("create_exam")) {
            String nameExam = word[2];
            LocalDateTime startDate = LocalDateTime.parse(word[3], timeFormat);
            LocalDateTime endDate = LocalDateTime.parse(word[4], timeFormat);
            createExam(timestamp, nameExam, startDate, endDate);
        //  comanda add_question
        } else if (word[1].equals("add_question")) {
            String typeQuestion = word[2];
            String nameExam = word[3];
            String author = word[4];
            int difficulty = Integer.parseInt(word[5]);
            double maxPoints = Double.parseDouble(word[6]);
            String textQuestion = word[7];
            String rightAnswer = word[8];
            //  apel metoda
            addQuestion(timestamp, typeQuestion, nameExam, author, difficulty, maxPoints, textQuestion, rightAnswer);
        //  comanda list_questions_history
        } else if (word[1].equals("list_questions_history")) {
            String nameExam = word[2];
            listHistoryQuestion(nameExam, path, timestamp);
        //  comanda print_exam
        } else if (word[1].equals("print_exam")) {
            String nameExam = word[2];
            printExam(nameExam, path, timestamp);
        //  comanda register_student
        } else if (word[1].equals("register_student")) {
            String nameStud = word[2];
            String group = word[3];
            registerStudent(nameStud, group);
        //  comanda submit_exam
        } else if (word[1].equals("submit_exam")) {
            String nameExam = word[2];
            String nameStud = word[3];
            int nrQuestions = exams.get(nameExam).getQuestionsSortByDiff().size();
            ArrayList<String> answers = new ArrayList<>();
            for (int i = 0; i < nrQuestions; i++) {
                answers.add(word[4 + i]);
            }
            submitExam(nameExam, nameStud, answers, timestamp, path);
        //  comanda show_student_score
        } else if (word[1].equals("show_student_score")) {
            String nameStud = word[2];
            String nameExam = word[3];
            showStudentScore(nameExam, nameStud, timestamp, path);
        //  comanda generate_report
        } else if (word[1].equals("generate_report")) {
            String nameExam = word[2];
            generateReport(nameExam, path, timestamp);
        //  comanda exit
        } else if (word[1].equals("exit")) {
            return;
        //  comanda invalida
        } else {
            System.out.println("Eroare - Comanda invalida");
            return;
        }
    }
}
