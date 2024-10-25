<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page isELIgnored="false" %>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
<!DOCTYPE html>
<html>
<head>
<link rel="icon" type="image/x-icon" href="/favicon.ico">
<meta charset="ISO-8859-1">
<title>Login Page</title>
<%@ include file="all_component/all_css.jsp" %>
</head>
<body>
<%@include file="all_component/navbar.jsp" %>
<c:if test="${userobj.role ne 'admin' }">
<c:redirect url="login.jsp"></c:redirect>
</c:if>


<form action="add_job" method="post">
  <div class="form-group">
    <label for="exampleFormControlInput1">Title</label>
    <input type="text" name="title" class="form-control" id="exampleFormControlInput1" placeholder="Title">
  </div>
  <div class="form-group">
    <label for="exampleFormControlSelect1">Category</label>
    <select class="form-control" name="category" id="exampleFormControlSelect1">
      <option>Technology</option>
      <option>Creative</option>
      <option>Marketing</option>
      <option>Finance</option>
      <option>Manufacturing</option>
    </select>
  </div>

  <div class="form-group">
    <label for="exampleFormControlSelect1">Status</label>
    <select class="form-control" name="status" id="exampleFormControlSelect1">
      <option>Active</option>
      <option>Inactive</option>
    </select>
  </div>

  <div class="form-group">
    <label for="exampleFormControlSelect1">Location</label>
    <select class="form-control" name="location" id="exampleFormControlSelect1">
      <option>Pune</option>
      <option>Mumbai</option>
      <option>Delhi</option>
      <option>Kolkata</option>
      <option>Bengaluru</option>
      <option>Surat</option>
      <option>Chennai</option>
      <option>NalaSopara</option>
      <option>Kelve Road</option>
    </select>
  </div>


  <div class="form-group">
    <label for="exampleFormControlTextarea1">Description</label>
    <textarea class="form-control" name="description" id="exampleFormControlTextarea1" rows="3"></textarea>
  </div>
  <button type="submit" class="btn btn-primary">Submit</button>
</form>


<%@include file="all_component/footer.jsp" %>
</body>
</html>
