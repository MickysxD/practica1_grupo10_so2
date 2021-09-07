#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>

#define  BUFSIZE 150

MODULE_LICENSE("A2");
MODULE_AUTHOR("MIGUEL ANGEL");
MODULE_DESCRIPTION("Modulo que muestra la informacion de la ram");
MODULE_VERSION("1.0");

struct sysinfo inf;
static int write_ram(struct seq_file * archivo, void *v){
    si_meminfo(&inf);
    long total_memoria = (inf.totalram * 4);
    long memoria_libre = (inf.freeram * 4);
    seq_printf(archivo, "{\n\t\"total\":%8lu,\n", total_memoria/1024);
    seq_printf(archivo, "\t\"uso\":%8lu\n}", (total_memoria-memoria_libre)/1024);
	return 0;
}

static int my_proc_open(struct inode *inode, struct file*file){
	return single_open(file, write_ram, NULL);	
}

static ssize_t my_proc_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos){
    return 0;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_proc_open,
    .release = single_release,
    .read = seq_read,
    .llseek = seq_lseek,
    .write = my_proc_write
};

static int ram_mod_init(void){
	proc_create("ram_p1", 0, NULL, &my_fops);
	printk(KERN_INFO "ram_p1: Hola mundo, somos el grupo 10");
 	return 0;
}

static void ram_mod_exit(void){
	remove_proc_entry("ram_p1",NULL);
	printk(KERN_INFO "ram_p1: Sayonara mundo, somos el grupo 10");
}


module_init(ram_mod_init);
module_exit(ram_mod_exit);