package com.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import com.entity.Jobs;

public class JobDao {
    private Connection connection;

    public JobDao(Connection connection) {
        super();
        this.connection = connection;
    }

    public boolean addJob(Jobs j) {
        boolean f = false;
        try {
            String sql = "INSERT INTO jobs (title, description, category, status, location) VALUES (?, ?, ?, ?, ?)";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setString(1, j.getTitle());
                ps.setString(2, j.getDescription());
                ps.setString(3, j.getCategory());
                ps.setString(4, j.getStatus());
                ps.setString(5, j.getLocation());
                int i = ps.executeUpdate();
                if (i == 1) {
                    f = true;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return f;
    }

    public List<Jobs> getAllJobs() {
        List<Jobs> jobList = new ArrayList<>();
        try {
            String sql = "SELECT * FROM jobs ORDER BY id DESC";
            try (PreparedStatement ps = connection.prepareStatement(sql);
                 ResultSet rs = ps.executeQuery()) {
                while (rs.next()) {
                    Jobs jobs = new Jobs();
                    jobs.setId(rs.getInt("id"));
                    jobs.setTitle(rs.getString("title"));
                    jobs.setDescription(rs.getString("description"));
                    jobs.setCategory(rs.getString("category"));
                    jobs.setStatus(rs.getString("status"));
                    jobs.setLocation(rs.getString("location"));
                    jobs.setPdate(rs.getString("pdate"));
                    jobList.add(jobs);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return jobList;
    }

    public Jobs getJobByID(int id) {
        Jobs job = null;
        try {
            String sql = "SELECT * FROM jobs WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setInt(1, id);
                try (ResultSet rs = ps.executeQuery()) {
                    if (rs.next()) {
                        job = new Jobs();
                        job.setId(rs.getInt("id"));
                        job.setTitle(rs.getString("title"));
                        job.setDescription(rs.getString("description"));
                        job.setCategory(rs.getString("category"));
                        job.setStatus(rs.getString("status"));
                        job.setLocation(rs.getString("location"));
                        job.setPdate(rs.getString("pdate"));
                    }
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return job;
    }

    public boolean updateJob(Jobs j) {
        boolean f = false;
        try {
            String sql = "UPDATE jobs SET title=?, description=?, category=?, status=?, location=? WHERE id=?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setString(1, j.getTitle());
                ps.setString(2, j.getDescription());
                ps.setString(3, j.getCategory());
                ps.setString(4, j.getStatus());
                ps.setString(5, j.getLocation());
                ps.setInt(6, j.getId());
                int i = ps.executeUpdate();
                if (i == 1) {
                    f = true;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return f;
    }

    public boolean deleteJob(int id) {
        boolean f = false;
        try {
            String sql = "DELETE FROM jobs WHERE id = ?";
            try (PreparedStatement ps = connection.prepareStatement(sql)) {
                ps.setInt(1, id);
                int i = ps.executeUpdate();
                if (i == 1) {
                    f = true;
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return f;
    }
}
