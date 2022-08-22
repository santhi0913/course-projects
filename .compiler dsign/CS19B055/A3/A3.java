// import syntaxtree.*;
// import visitor.*;

// public class Main {
//    public static void main(String [] args) {
//       try {
//          //System.out.println("Program parsed successfully haha");
//          Node root = new MiniJavaParser(System.in).Goal();
//          //System.out.println("Program parsed successfully haha");
//           //root.accept(new GJDepthFirst()); // Your assignment part is invoked here.
//          // root.accept(new copyDF(),null);
//          Object table = root.accept(new GJDepthFirst(), null);
//          //System.out.println("DF done ");
//          // if(table != null)
//          //    System.out.println("table not null");
//          //root.accept(new typecheckpass(), table);
//          System.out.println("Program type checked successfully");
//       }
//       catch (ParseException e) {
//          System.out.println(e.toString());
//       }
//    }
// } 

import syntaxtree.*;
import visitor.*;
import java.util.*;

public class A3 {
   public static void main(String [] args) {
      try {
         Node root = new MiniJavaParser(System.in).Goal();
         
         //tablegenerator TG = new tablegenerator();
         Hashtable <String, classtable> SymbolTable = new Hashtable <String, classtable>();
         Hashtable <String, classtable> newSymbolTable = new Hashtable <String, classtable>();
         myobject O = new myobject();
         
         Object firstpass = root.accept(new tablegenerator(), SymbolTable); 
         newSymbolTable = (Hashtable <String, classtable>) firstpass;
         Object secondpass = root.accept(new parse2(), newSymbolTable); 
         O = (myobject) secondpass;

         //IRGenerator IR = new IRGenerator();
         // if (O == null){
         //    System.out.println("O is null\n");
         // }
         Object thirdpass = root.accept(new IRGenerator(), O);

         // System.out.println(O.NewSymTab.get("A").MethDec.get("foo").index);
         // System.out.println(O.NewSymTab.get("A").MethDec.get("bar").index);
         // System.out.println(O.NewSymTab.get("B").MethDec.get("foo").index);
         // System.out.println(O.NewSymTab.get("B").MethDec.get("bar").index);
         // System.out.println(O.NewSymTab.get("B").MethDec.get("foobar").index);
      }
      catch (ParseException e) {
         System.out.println(e.toString());
      }
   }
}