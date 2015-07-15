A=importdata('Spin20_54');
A_new = zeros(size(A,1),2);
for i=1:size(A,1)
    A_new(i,1) = A(i,1) - A(i,2);
end

for j=1:size(A,1)
    A_new(j,2) = A(j,1) + A(j,2);
end

A_new = A_new/1000;

B=linspace(-1,1,2000);
B_plot = zeros(1,2000);
for i=1:2000
  B_plot(i) = (1+B(i)*B(i))/2;
end


plot(A_new(:,1),A_new(:,2)); hold on
plot(B,B_plot);
