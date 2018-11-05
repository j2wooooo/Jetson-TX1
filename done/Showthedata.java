import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.*; 
	  
public class Showthedata
{ 
	static Vector cols;
	static Vector rows;
	static Vector<String> photo;
	static DefaultTableModel model;
	static JTable jTable;
	static JScrollPane scrollpane;
	static JPanel panel;
	static JButton btnInsert;
	static JFrame jFrame;
	 
	static String year;
        static String month;
        static String day;
        static String place;
        static String time;
        static String photo_name;
	static int flag;
	 
	static Dimension dimforphoto;
	static Dimension dimfortable;
	public static void main( String[] args )  
	{  
		Dimension dimforwindow = new Dimension(680,599);
		
		jFrame = new JFrame("SHOW THE DATA");
		dimfortable = new Dimension(630,400);
		dimforphoto = new Dimension(680,599);

		cols = new Vector();
		photo = new Vector<String>();

		cols.add("년");
		cols.add("월");
		cols.add("일");
		cols.add("시간");
		cols.add("장소");

		connectiong();
		 
		jFrame.setPreferredSize(dimforwindow);
		jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	     jFrame.pack();
		 
	     	making_GUI();	
	  }
	
	
	@SuppressWarnings("unchecked")
	public static void making_data()
	{
		Vector data = new Vector();
		//

		data.add(year);
		data.add(month);
		data.add(day);
		data.add(time);
		data.add(place);
			 
		photo.add(photo_name);
		rows.add(data); 
	
		 
		model = new DefaultTableModel(rows,cols){
			    @Override
			    public boolean isCellEditable(int rows, int column) {
			       //all cells false
			       return false;
			    }
			};
	}

	public static void making_GUI()
	{
	
		jTable = new JTable(model);	
		jTable.addMouseListener(new MouseAdapter () { 
	    	 
	    	@Override
	    	public void mouseClicked(MouseEvent e) 
	    	{
			System.out.println("You clicked double");
	    		int selected = jTable.getSelectedRow();
			System.out.println(selected);
	    		if(selected<0) {return;}                           

	    		if (e.getClickCount() == 2)  // 더블클릭
	    		{
				
	    			JFrame iFrame;

				String file_name = "/home/nvidia/darknet/pictures/";

				//fime_name.concat(photo.elementAt(selected).concat(".jpg"));
				String pic_name = file_name + photo.elementAt(selected) +".jpg";
				System.out.println(pic_name);
	    			ImageIcon back_icon = new ImageIcon(pic_name); // 해당하는 줄에 있는 사진을 띄운다.
				//back_icon.concat(file_name);
	    			Image background_img = back_icon.getImage().getScaledInstance(742,599,java.awt.Image.SCALE_SMOOTH); // resize image
				
				
				System.out.println(dimforphoto);
	    			JLabel Ilabel = new JLabel(new ImageIcon(background_img));
	    			 
	    			//해당하는 이미지를 다른 창에 띄운다.
	    			iFrame = new JFrame("USER INFORMATION");
	    			iFrame.add(Ilabel);
	    			iFrame.setPreferredSize(dimforphoto);
	    			iFrame.addWindowListener(new WindowAdapter() { // 새로 생긴 창만 꺼지게 하려고
	    				public void windowClosing(WindowEvent e) {
	    					iFrame.setVisible(false);
	    					iFrame.dispose();
	    				}
	    			});

	    		        iFrame.pack();
	    			iFrame.setVisible(true);
	    		}
	    	}
	    });
	    scrollpane = new JScrollPane(jTable);
	     panel = new JPanel();

	     //jTable.getColumn("").setCellRenderer(new Button);
	     //자바 테이븝에 클릭 이벤트 
	     
	     
	     
	     btnInsert = new JButton("새로고침");
	     
	     scrollpane.setLocation(10,100);
	     scrollpane.setSize(dimfortable);
	     scrollpane.setEnabled(false);
	     
	     panel.add(scrollpane);
	     panel.add(btnInsert);
	     panel.setLayout(null);
	     
	     btnInsert.setSize(100,50);
	     btnInsert.setLocation(300, 20);
	     btnInsert.addActionListener(new ActionListener() {
	            @Override
	            public void actionPerformed(ActionEvent e) {
	                // TODO Auto-generated method stub
	                
	               connectiong();
	            }
	        });
	     jFrame.add(panel);
	     jFrame.setVisible(true);
	}
	 
	public static void connectiong()// MySQL이랑 연결
	{
   		 Connection conn = null ;
        	// mysql 연동
		String url = "jdbc:mysql://localhost/ckdb";
        	String userId = "root";  
        	String userPass = "123123" ;

        	try{
        		Class.forName("com.mysql.jdbc.Driver");
        		System.out.println("Driver OK!!!");
        		conn = DriverManager.getConnection(url, userId, userPass);  
        		System.out.println("Conn OK!!!");
        	
        		// 데이터베이스 연결 성공!!
        	
        		// select 쿼리
           	 	// 데이터 불러오기
            
            		String qu = "select * from user;";
            		// java statement 생성
           		Statement st = conn.createStatement();
        			// 쿼리 execute, 객체 형성
            		ResultSet rs = st.executeQuery(qu);

            		rows = new Vector();

            		// 각 열을 반복적으로 나타내줌
           		 while(rs.next()) {
            			year = rs.getString("Year");
            			month = rs.getString("Month");
            			day = rs.getString("Day");
            			place = rs.getString("Place");
            			time = rs.getString("Time");
            			photo_name = rs.getString("Photo_name");
            	
				making_data();
				//making_GUI();
            			System.out.format("%s %s %s %s %s %s\n", year, month, day, place, time, photo_name);
            	
            		}
           		 st.close();                                                        
            
        		} catch(Exception e) {
        			System.out.println("ERROR!!");
        			e.printStackTrace();
       			}
	}
}   
