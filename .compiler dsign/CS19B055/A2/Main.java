import syntaxtree.*;
import visitor.*;

public class Main {
   public static void main(String [] args) {
      try {
         //System.out.println("Program parsed successfully haha");
         Node root = new MiniJavaParser(System.in).Goal();
         //System.out.println("Program parsed successfully haha");
          //root.accept(new GJDepthFirst()); // Your assignment part is invoked here.
         // root.accept(new copyDF(),null);
         Object table = root.accept(new GJDepthFirst(), null);
         //System.out.println("DF done ");
         // if(table != null)
         //    System.out.println("table not null");
         //root.accept(new typecheckpass(), table);
         System.out.println("Program type checked successfully");
      }
      catch (ParseException e) {
         System.out.println(e.toString());
      }
   }
} 

