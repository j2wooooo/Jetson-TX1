import java.sql.*;  
  
public class MainClass  
{  
    public static void main( String[] args )  
    {  
        Connection conn = null ;  
    
        // mysql 연동
        //String url = "jdbc:mysql://localhost?serverTimezone=UTC";  
        String url = "jdbc:mysql://localhost?serverTimezone=UTC&useUnicode=true&characterEncoding=UTF-8&useFastDateParsing=false&useSSL=false&nullNamePatternMatchesAll=true&&nullCatalogMeansCurrent=true";
        String userId = "root";  
        String userPass = "123123" ;        

        try{
        	Class.forName("com.mysql.cj.jdbc.Driver");
        	System.out.println("Driver OK!!!");
        	conn = DriverManager.getConnection(url, userId, userPass);  
        	System.out.println("Conn OK!!!");
        	
        	// 데이터베이스 연결 성공!!
        	
        	// select 쿼리
            // 데이터 불러오기
            
            String qu = "select * from user";
            // java statement 생성
            Statement st = conn.createStatement();
        	// 쿼리 execute, 객체 형성
            ResultSet rs = st.executeQuery(qu);
            
            // 각 열을 반복적으로 나타내줌
            while(rs.next()) {
            	String year = rs.getString("Year");
            	String month = rs.getString("Month");
            	String day = rs.getString("Day");
            	String place = rs.getString("Place");
            	String time = rs.getString("Time");
            	String photo_name = rs.getString("Photo_name");
            	
            	System.out.format("%s %s %s %s %s %s\n", year, month, day, place, time, photo_name);
            	
            }
            st.close();                                                          
            
        } catch(Exception e) {
        	System.out.println("ERROR!!");
        	e.printStackTrace();
        }
        
    }
}   
