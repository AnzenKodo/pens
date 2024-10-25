package com.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

import com.entity.Jobs;
import com.entity.User;

public class UserDao {

	private Connection connection;

	public UserDao(Connection connection) {
		super();
		this.connection = connection;
	}
	
	public boolean addUser(User u) {
		
		boolean f=false;
		try {
			String sql = "insert into user (name,email,password,qualification,role ) values (?,?,?,?,?)";
			PreparedStatement ps =connection.prepareStatement(sql);
			ps.setString(1, u.getName());
			ps.setString(2, u.getEmail());
			ps.setString(3, u.getPassword());
			ps.setString(4, u.getQualification());
			ps.setString(5, u.getRole());
			
			int i = ps.executeUpdate();
			
			if(i==1) {
				f=true;
			}
		
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return f;
	}
	
	public User validateUser(String username, String password) {
		User user= null;
		try {
			String sql = "select * from user where email=? and password=?";
			PreparedStatement ps =connection.prepareStatement(sql);			
			ps.setString(1, username);
			ps.setString(2, password);
			ResultSet rs=ps.executeQuery();
			while (rs.next()) {
				user= new User();
				user.setId(rs.getInt(1));
				user.setName(rs.getString(2));
				user.setEmail(rs.getString(3));
				user.setQualification(rs.getString(5));
				user.setRole(rs.getString(6));								
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		return user;
	}
}
